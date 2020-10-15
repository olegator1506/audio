#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <netdb.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <strings.h>
#include <string.h>
#include <string>
#include <unistd.h>
#include <jsoncpp/json/json.h>
#include <iostream>

#include "pcf/pcf.h"
#include "adau17x/adau17x.h"
#include "log/log.h"
#include "alsaplayer/control.h"
#include "src/classes/selector.h"
#include "config.h"



extern bool serverRun(void);
extern bool initServer(void);

#define LOCAL_DEBUG 1




#pragma GCC diagnostic ignored "-Wwrite-strings"
#define SLAVE_ADDRESS 0x20
static const char *TAG = "Main";

int alsaSessionNum;

#ifdef LOCAL_DEBUG
bool setup(void) {
	DBG(TAG,"Initialization");
	pcfInit();
	adauInit(ADAU_CHIP_ADDRESS);
	Selector = new TSelector();
	return true;	
}
#else
bool setup(void) {
	DBG(TAG,"Initialization");
/*
	if(!ap_find_session(ALSA_PLAYER_SESSION_NAME,&alsaSessionNum)) {
		LOGE(TAG,"AlsaPlayer not started");
		return false;
	}
*/
	DBG(TAG,"AP session ID =%d\n", alsaSessionNum);
	if(!pcfInit()) return false;
//	if(!pcfSelAnalogInput(1)) return false;
	if(!adauInit(ADAU_CHIP_ADDRESS)) return false;
	Selector = new TSelector();
	return true;	
}
#endif

int main(int argc, char **argv)
{

	setLogLevelGlobal(LOG_LEVEL);
	LOGI(TAG,"program started");
 	if(!setup()) {
		puts("Initialization error"); 
	}
	LOGI(TAG,"program started");
	initServer();
	serverRun();
	Selector->finish();
	LOGI(TAG,"program finished");
    return 0;

}

