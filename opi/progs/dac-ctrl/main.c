#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "i2c/i2c.h"
#define SLAVE_ADDRESS 0x20
int main(int argc, char **argv)
{
	unsigned char bw,br;
	int i;
/*
	if(!i2cOpen()) {
		printf("Error opening I2C device\n");
		exit(1);
	}
*/
 
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
    return 0;
}
