#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "i2c/i2c.h"
#include "log/log.h"
#include "config.h"

#define SLAVE_ADDRESS 0x20
const char *TAG = "Main";

bool setup(void) {
	LOGI(TAG,"Initialization");
	uint8_t b = 0x40;
	if(!i2cWriteCheck(SLAVE_ADDRESS,&b)) return false;
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

