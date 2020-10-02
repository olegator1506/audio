#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pcf/pcf.h"
#include "adau17x/adau17x.h"
#include "log/log.h"
#include "config.h"

#define SLAVE_ADDRESS 0x20
static const char *TAG = "Main";

bool setup(void) {
	LOGI(TAG,"Initialization");
	if(!pcfInit()) return false;
	if(!adauInit(ADAU_CHIP_ADDRESS)) return false;
	return true;	
}

int main(int argc, char **argv)
{
	setLogLevelGlobal(LOG_LEVEL);
	LOGI(TAG,"program started");
	if(!setup()) {
		puts("Initialization error"); 
	}
	LOGI(TAG,"program started");
	LOGI(TAG,"program finished");
    return 0;
}

