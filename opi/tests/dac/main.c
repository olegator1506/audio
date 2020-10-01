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
	return true;	
}

int main(int argc, char **argv)
{
	unsigned char bw,br;
	int i;
	setLogLevelGlobal(LOG_LEVEL);
	LOGI(TAG,"program started");
	setup();
	for(i = 0; i <256; i++) {
		bw = i & 0xff;
		if (!i2cWrite(SLAVE_ADDRESS, &bw, 1))
		{
			perror("Failed to write to the i2c bus");
			exit(1);
		}
 
    // Read a byte from the slave.
		if (!i2cRead(SLAVE_ADDRESS,&br,1))
		{
			perror("Failed to read from the i2c bus");
			exit(1);
		}
		if(br != bw) printf("Error: write %02x read %02x", bw,br);
	}
	LOGI(TAG,"program finished");
    return 0;
}
 
/* 
int main(int argc, char **argv) {
	printf("Hello world");
}
 */