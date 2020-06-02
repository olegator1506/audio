#ifndef _HTTP_SERVER_H_
#define _HTTP_SERVER_H_
#include <esp_err.h>
extern esp_err_t start_webserver(void);
extern void stop_webserver(void);
#endif