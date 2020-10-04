#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pcf/pcf.h"
#include "adau17x/adau17x.h"
#include "log/log.h"
#include "alsaplayer/control.h"
#include "config.h"

#pragma GCC diagnostic ignored "-Wwrite-strings"
#define SLAVE_ADDRESS 0x20
static const char *TAG = "Main";

int alsaSessionNum;

bool setupx(void) {
	DBG(TAG,"Initialization");
	if(!ap_find_session(ALSA_PLAYER_SESSION_NAME,&alsaSessionNum)) {
		LOGE(TAG,"AlsaPlayer not started");
		return false;
	}
	DBG(TAG,"AP session ID =%d\n", alsaSessionNum);
	if(!pcfInit()) return false;
	if(!pcfSelAnalogInput(1)) return false;
	if(!adauInit(ADAU_CHIP_ADDRESS)) return false;
	return true;	
}

int main(int argc, char **argv)
{
	setLogLevelGlobal(LOG_LEVEL);
	LOGI(TAG,"program started");
	if(!setupx()) {
		puts("Initialization error"); 
	}
	LOGI(TAG,"program started");
	LOGI(TAG,"program finished");
    return 0;
}

