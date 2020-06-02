#ifndef _MQTT_H_
#define _MQTT_H_
#include <esp_err.h>
extern esp_err_t mqttStart(void);
extern esp_err_t mqttReconnect(void);
extern esp_err_t mqttPublish(const char *topic, const char * data);
#endif