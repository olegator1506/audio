#include <stdlib.h>
#include <esp_log.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include <sys/param.h>
#include <esp_event.h>
#include "esp_system.h"
#include "esp_wifi.h"
#include "config.h"

//#include "common.h"
//#include "http-server.h"
//#include "st7735.h"
#ifdef USE_MQTT
#include <mqtt.h>
#endif
#define EXAMPLE_ESP_MAXIMUM_RETRY 50

const int WIFI_CONNECTED_BIT = BIT0;
static const char *TAG="net";
static EventGroupHandle_t s_wifi_event_group;
static int s_retry_num = 0;
static bool _wifiConnected = false;

extern esp_err_t tcpServerStart();
extern esp_err_t tcpServerStop();

extern esp_err_t otaStart();
extern esp_err_t otaStop();


/*
static void disconnect_handler(void* arg, esp_event_base_t event_base, 
                               int32_t event_id, void* event_data)
{

    httpd_handle_t* server = (httpd_handle_t*) arg;
    if (*server) {
        ESP_LOGI(TAG, "Stopping webserver");
        stop_webserver(*server);
        *server = NULL;
    }
    
}
static void connect_handler(void* arg, esp_event_base_t event_base, 
                            int32_t event_id, void* event_data)
{
    ESP_LOGI(TAG,"Start connect handler");
    httpd_handle_t* server = (httpd_handle_t*) arg;
    if (*server == NULL) {
        ESP_LOGI(TAG, "Starting webserver");
        ESP_ERROR_CHECK(start_webserver());
    }
    
}
*/

static void event_handler(void* arg, esp_event_base_t event_base, 
                                int32_t event_id, void* event_data)
{
    char pBuf[128];
    ESP_LOGI(TAG,"Event %s:%d",event_base,event_id);
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        _wifiConnected = false;
        esp_wifi_connect();
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        _wifiConnected = false;
        tcpServerStop();
//        stop_webserver();
        otaStop();
        esp_wifi_connect();
        xEventGroupClearBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
        s_retry_num++;
        ESP_LOGI(TAG, "retry to connect to the AP");
        ESP_LOGI(TAG,"connect to the AP fail");
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        _wifiConnected = true;
        ESP_LOGI(TAG,"WiFi connected");
//        start_webserver();
        tcpServerStart();
        otaStart();

#ifdef USE_MQTT
            mqttReconnect();
#endif
        ESP_LOGI(TAG, "got ip:" IPSTR, IP2STR(&event->ip_info.ip));
        sprintf(pBuf,"IP:%d.%d.%d.%d",IP2STR(&event->ip_info.ip));
//        ST7735_WriteString(2,13,pBuf,Font_7x10,ST7735_BLACK,ST7735_CYAN);
        s_retry_num = 0;
        xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
    } else {

    }
}



void wifi_init_sta(void)
{
    s_wifi_event_group = xEventGroupCreate();

    tcpip_adapter_init();

    
//    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));


    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &event_handler, NULL));
//    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, WIFI_EVENT_STA_DISCONNECTED, &disconnect_handler, NULL));

    wifi_config_t wifi_config = {
        .sta = {
            .ssid = WIFI_SSID,
            .password = WIFI_PASSWORD
        },
    };
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA) );
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config) );
    ESP_ERROR_CHECK(esp_wifi_start() );

    ESP_LOGI(TAG, "wifi_init_sta finished.");
    ESP_LOGI(TAG, "connect to ap");
}


void netKeepAlive(time_t t){
    static char s[20];
    utoa(t,s,10);
#ifdef USE_MQTT
    mqttPublish("keepAlive",s);
#endif    
}

bool wifiConnected(void){
    return _wifiConnected;
}

esp_err_t netInit(void) {
    _wifiConnected = false;
    wifi_init_sta();
//    start_webserver();
#ifdef USE_MQTT    
    ESP_ERROR_CHECK(mqttStart());
#endif    
    return ESP_OK;
}