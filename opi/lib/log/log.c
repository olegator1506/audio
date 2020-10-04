#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <time.h>
#include <sys/time.h>

#include "log.h"

#define LOG_MAX_STRING_LENGTH 256

static char _buf[LOG_MAX_STRING_LENGTH+1];
static const char *_logLevelStr[] = {
		"","ERR","WARN","INFO","DBG","VERB"
};
static log_level_t _logLevelGlobal = 0;

void setLogLevelGlobal(log_level_t level) {
	_logLevelGlobal = level;
}

static bool _needOutput(const char *tag, log_level_t level){
	if(_logLevelGlobal == LOG_NONE) return false;
	if(level > _logLevelGlobal) return false;
	return true;
}



void _log(const char *tag, log_level_t level, const char *format, va_list list)
{
	if(!_needOutput(tag,level)) return;
	vsnprintf(_buf, LOG_MAX_STRING_LENGTH, format,list);
	printf("%s: %s\n",_logLevelStr[level],_buf);
}
void LOGE(const char *tag,const char *format,...) {
	va_list list; 
	va_start(list,format);
	_log(tag, LOG_ERROR, format, list);
	va_end(list);
}	

void LOGI(const char *tag,const char *format,...) {
	va_list list; 
	va_start(list,format);
	_log(tag, LOG_INFO, format, list);
	va_end(list);
}	
void LOGW(const char *tag,const char *format,...) {
	va_list list; 
	va_start(list,format);
	_log(tag, LOG_WARN, format, list);
	va_end(list);
}	

void DBG(const char *tag,const char *format,...) {
	va_list list; 
	va_start(list,format);
	_log(tag, LOG_DEBUG, format, list);
	va_end(list);
}

void VERB(const char *tag,const char *format,...) {
	va_list list; 
	va_start(list,format);
	_log(tag, LOG_VERBOSE, format, list);
	va_end(list);
}	


	