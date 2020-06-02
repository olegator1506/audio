 #include <Arduino.h>
 #include "debug.h"
 #include <stdarg.h>
 #include "config.h"

bool debugMode = false;
bool debugSerial = false;

void _debugOut(char *buf){
  if(debugSerial)
    Serial.println(buf);
}

void DBG(const char *fmt, ... ){
  if(!debugMode) return;
  char buf[DEBUG_STR_LEN]; // resulting string limited to 128 chars
  va_list args;
  va_start (args, fmt );
  vsnprintf(buf, DEBUG_STR_LEN-1, (const char *)fmt, args);
  va_end (args);
  _debugOut(buf);
 }
#ifdef F 
void DBG(const __FlashStringHelper *fmt, ... ){
  if(!debugMode) return;
  char buf[DEBUG_STR_LEN]; // resulting string limited to 128 chars
  va_list args;
  va_start (args, fmt );
  vsnprintf_P(buf, DEBUG_STR_LEN, (const char*)fmt, args);
  va_end (args);
  _debugOut(buf);
}
#endif

/*
void checkFreeRam(){
#ifdef __DEBUG__
  extern int __heap_start, *__brkval; 
  static int freeRam;
  int curFree =  (int) &curFree - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
  if(curFree != freeRam) {
    freeRam = curFree;
    DBG(printf("Free RAM = %d\n",freeRam));
    if(freeRam < 500){
      Serial.print("Free RAM "); Serial.println(freeRam);
    }  
  } 
#endif
}
*/