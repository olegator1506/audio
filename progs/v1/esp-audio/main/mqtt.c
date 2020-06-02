#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#include "esp_log.h"
#include "mqtt_client.h"

#define MQTT_BASE "/SweetHome/audio/"
#define MQTT_SUBSCRIBE "/SweetHome/audio/#"
#define MQTT_BROKER_URL "mqtt://192.168.253.20"

static const char *TAG = "MQTT";
static esp_mqtt_client_handle_t _mqttClient;
static bool _connected=false;
static bool _subscribed=false;
//ststic char* _publishTopic = NULL;
//ststic char* _publishData = NULL; 
//static size_t _lastTopicLen = 0;
//static size_t _lastDataLen = 0;
static esp_err_t mqtt_event_handler_cb(esp_mqtt_event_handle_t event)
{
    esp_mqtt_client_handle_t client = event->client;
    int msg_id;
    // your_context_t *context = event->context;
    switch (event->event_id) {
        case MQTT_EVENT_CONNECTED:
            ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
            _connected = true;
            msg_id = esp_mqtt_client_subscribe(client, "", 0);
            ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);

            msg_id = esp_mqtt_client_subscribe(client, MQTT_SUBSCRIBE, 1);
            ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);
            break;
        case MQTT_EVENT_DISCONNECTED:
            _connected = false;
            ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
            break;
        case MQTT_EVENT_SUBSCRIBED:
            ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
            _subscribed=true;
            break;
        case MQTT_EVENT_UNSUBSCRIBED:
            ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
            _subscribed=false;
            break;
        case MQTT_EVENT_PUBLISHED:
            ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_DATA:
            ESP_LOGI(TAG, "MQTT_EVENT_DATA");
            printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
            printf("DATA=%.*s\r\n", event->data_len, event->data);
            break;
        case MQTT_EVENT_ERROR:
            ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
            break;
        default:
            ESP_LOGI(TAG, "Other event id:%d", event->event_id);
            break;
    }
    return ESP_OK;
}

static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data) {
    ESP_LOGD(TAG, "Event dispatched from event loop base=%s, event_id=%d", base, event_id);
    mqtt_event_handler_cb(event_data);
}

esp_err_t mqttReconnect(void){
    ESP_LOGI(TAG,"Exec reconnect");
//   return esp_mqtt_client_reconnect(_mqttClient);
    return esp_mqtt_client_start(_mqttClient);
}

esp_err_t mqttStart(void)
{
    esp_mqtt_client_config_t mqtt_cfg = {
        .uri = MQTT_BROKER_URL,
    };
    _mqttClient = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_register_event(_mqttClient, ESP_EVENT_ANY_ID, mqtt_event_handler, _mqttClient);
    return esp_mqtt_client_start(_mqttClient);
}

esp_err_t mqttPublish(const char *topic, const char * data){
    ESP_LOGI(TAG,"Publish %s = %s",topic,data);
    if(!_connected) {
        ESP_LOGE(TAG,"Publish fail: not connected");
        return ESP_FAIL;
    }    
/*    size_t tLen = strlen(topic) + strlen(MQTT_BASE) + 2;
    size_t dLen = strlen(data) + 1;
    if(_publishTopic) free(_publishTopic);
    if(_publishData) free(_publishData);
    _publishTopic = NULL;
    _publishData = NULL;
    _publishTopic = (char *)malloc(tLen);
    if(!_publishTopic) return ESP_ERR_NO_MEM;
    _publishData = (char *)malloc(dLen);
    if(!_publishData) return ESP_ERR_NO_MEM;
*/
    size_t tLen = strlen(topic) + strlen(MQTT_BASE) + 2;
    char *tt = malloc(tLen);
    if(!tt) return ESP_ERR_NO_MEM;
    snprintf(tt, tLen,"%s%s",MQTT_BASE,topic);
    int res = esp_mqtt_client_publish(_mqttClient,tt,data,0,1,0);
    free(tt);
    if(res == -1) return ESP_FAIL;
    return ESP_OK;
} 

/*
void app_main(void)
{
    ESP_LOGI(TAG, "[APP] Startup..");
    ESP_LOGI(TAG, "[APP] Free memory: %d bytes", esp_get_free_heap_size());
    ESP_LOGI(TAG, "[APP] IDF version: %s", esp_get_idf_version());
    esp_log_level_set("*", ESP_LOG_INFO);
    esp_log_level_set("MQTT_CLIENT", ESP_LOG_VERBOSE);
    esp_log_level_set("MQTT_EXAMPLE", ESP_LOG_VERBOSE);
    esp_log_level_set("TRANSPORT_TCP", ESP_LOG_VERBOSE);
    esp_log_level_set("TRANSPORT_SSL", ESP_LOG_VERBOSE);
    esp_log_level_set("TRANSPORT", ESP_LOG_VERBOSE);
    esp_log_level_set("OUTBOX", ESP_LOG_VERBOSE);

    ESP_ERROR_CHECK(nvs_flash_init());
    esp_netif_init();
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    mqtt_app_start();
}
*/