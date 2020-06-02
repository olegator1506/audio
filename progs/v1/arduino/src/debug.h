#ifndef __DEBUG_H__
#define __DEBUG_H__
extern bool debugMode,debugSerial;
void DBG(const char *fmt, ... );
#ifdef F 
void DBG(const __FlashStringHelper *format, ... );
#endif
#define DEBUG_STR_LEN 100
void checkFreeRam(void);
#endif