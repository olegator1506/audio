#include <esp_log.h>
#include <esp_http_server.h>
#include <sys/param.h>
#include <esp_event.h>
#include "channel.h"

static httpd_handle_t server = NULL;
static const char *TAG="http-server";
const char *successResponse = "Ok";





static esp_err_t execSetChannel(httpd_req_t *req,const char *paramStr) {
    char param[32];
    int ch;
    ESP_LOGI(TAG,"Exec set channel");
    if(httpd_query_key_value(paramStr,"channel",param,sizeof(param)) != ESP_OK) {
        ESP_LOGI(TAG,"Channel number not specified in request");
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Channel number not specified");
        return ESP_FAIL;
    }
    ch = atoi(param);
    if((ch < 1) || ch > channelCount()) {
        ESP_LOGI(TAG,"Invalid channel number = %d",ch);
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Invalid channel number");        
        return ESP_FAIL;
    } 
    channelSelect(ch - 1);// В запросе номер канала нумеруется от 1, в chList от 0
    ESP_LOGI(TAG,"Select channel # %d",ch);
    return ESP_OK;
}


static esp_err_t _sendErrorResponse(httpd_req_t *req,const char *errorMessage) {
    ESP_LOGE(TAG,"%s",errorMessage);
    httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, errorMessage);
    return ESP_FAIL;
}



/**
 * @summary Обработчик запросов /api (метод GET)
*/

static esp_err_t _apiRqHandler(httpd_req_t *req)
{
    char buf[128],action[32],param[32];
    int ch;
    esp_err_t result = ESP_FAIL;
    httpd_req_get_url_query_str(req, buf,127);
    if(httpd_query_key_value(buf,"action",action,sizeof(action)) != ESP_OK) {
        return _sendErrorResponse(req,"Invalid response: mandatory parameter \"action\" not specified");    
    }
    if(strcmp(action,"set_channel") == 0) {
        result = ESP_OK;
        ESP_LOGI(TAG,"Request set channel");
        if(httpd_query_key_value(buf,"channel",param,sizeof(param)) != ESP_OK) 
            return _sendErrorResponse(req,"Channel number not specified");
        ch = atoi(param);
        ESP_LOGI(TAG,"Channel # %d",ch);
        if((ch < 1) || ch > channelCount()) 
            return _sendErrorResponse(req,"Invalid channel number");
        channelSelect(ch - 1);// В запросе номер канала нумеруется от 1, в chList от 0
    }
    else if(strcmp(action,"folder") == 0) {
        ESP_LOGI(TAG,"Request folder");
        if(httpd_query_key_value(buf,"folder",param,sizeof(param)) != ESP_OK) 
            return _sendErrorResponse(req,"Invalid request: folder number not specified");
        ch = atoi(param);
        result = selectFolder(ch); 
    } 
    else if(strcmp(action,"prevfolder") == 0) {
        ESP_LOGI(TAG,"Request previous folder");
        result = channelPrevFolder();
    }
    else if(strcmp(action,"nextfolder") == 0) {
        ESP_LOGI(TAG,"Request next folder");
        result = channelNextFolder();
    }
    else if(strcmp(action,"play") == 0) {
        ESP_LOGI(TAG,"Request play");
        result = channelPlay();
    }
    else if(strcmp(action,"next") == 0) {
        ESP_LOGI(TAG,"Request next track");
        result = channelNextTrack();
    }
    else if(strcmp(action,"prev") == 0) {
        ESP_LOGI(TAG,"Request previous track");
        result = channelPrevTrack();
    }
    else if(strcmp(action,"pause") == 0) {
        ESP_LOGI(TAG,"Request pause");
        result = channelPause();
    }
    else if(strcmp(action,"resume") == 0) {
        ESP_LOGI(TAG,"Request resume");
        result = channelResume();
    }
    else if(strcmp(action,"switchpause") == 0) {
        ESP_LOGI(TAG,"Request switch pause");
        result = channelSwitchPause();
    }
    else if(strcmp(action,"stop") == 0) {
        ESP_LOGI(TAG,"Request stop");
        result = channelStop();
    }
    else if(strcmp(action,"volume") == 0) {
        ESP_LOGI(TAG,"Request volume");
        if(httpd_query_key_value(buf,"volume",param,sizeof(param)) != ESP_OK) 
            return _sendErrorResponse(req,"Invalid request: parameter \"volume\" not specified");
        ch = atoi(param);
        result = channelVolume(ch); 
    }
    else if(strcmp(action,"eq") == 0) {
        ESP_LOGI(TAG,"Request equalizer");
        if(httpd_query_key_value(buf,"mode",param,sizeof(param)) != ESP_OK) 
            return _sendErrorResponse(req,"Invalid request: parameter \"volume\" not specified");
        ch = atoi(param);
        result = channelEqualizer(ch); 
    }
    else result = ESP_FAIL;
//    free(buf);
    if(result == ESP_FAIL) 
        _sendErrorResponse(req, channelErrorMessaage);
    else { 
	httpd_resp_set_hdr(req,"Access-Control-Allow-Origin","*");
        httpd_resp_send(req, successResponse, strlen(successResponse));
    }
    return ESP_OK;
}


static const httpd_uri_t apiRqConf = {
    .uri       = "/api",
    .method    = HTTP_GET,
    .handler   = _apiRqHandler,
    .user_ctx  = NULL
};


esp_err_t start_webserver(void)
{
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    // Start the httpd server
    ESP_LOGI(TAG, "Starting server on port: '%d'", config.server_port);
    if (httpd_start(&server, &config) == ESP_OK) {
        // Set URI handlers
        ESP_LOGI(TAG, "Registering URI handlers");
        httpd_register_uri_handler(server, &apiRqConf);
//        httpd_register_uri_handler(_httpServer, &echo);
//        httpd_register_uri_handler(_httpServer, &ctrl);
        return ESP_OK;    
    }

    ESP_LOGI(TAG, "Error starting server!");
    return ESP_FAIL;
}

void stop_webserver(void)
{
    // Stop the httpd server
    httpd_stop(server);
}

