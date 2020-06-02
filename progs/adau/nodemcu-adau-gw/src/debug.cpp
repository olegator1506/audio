#include <Arduino.h> 
#include <stdarg.h>
#include <stdbool.h>

bool debugMode = false;
#define DEBUG_STR_LEN 256
#define DEBUG_PORT &huart2
void _debugOut(char *buf){
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

char *dbgDataStr(const uint8_t *data, int len) {
  static char s[255];
  int l = len;
  if(l >20) l =20;
  memset(s,0,255);
  for(int i=0;i<l;i++)
    sprintf(s+i*3,"%02X ",data[i]);
//  Serial.println(s);  
//  DBG("Checkpoint 1");  
  return s;  
}
