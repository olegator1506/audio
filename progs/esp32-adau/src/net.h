#ifndef _HTTP_H_
#define _HTTP_H_
#include <esp_err.h>
extern esp_err_t netInit(void);
//extern esp_err_t netKeepAlive(time_t t);
extern bool wifiConnected(void);
#endif