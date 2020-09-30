#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <stdbool.h>
#include <fcntl.h>

#define I2C_DEV_NAME  "/dev/i2c-0"
#define I2C_RETRY_TIMEOUT 1000 // пауза между последовательными попытками
#define I2C_RETRY_COUNT 1

static int _file = 0;
static int _lastDeviceAddress;

static void _setAddress(int address) {
	if(_lastDeviceAddress != address) {
		_lastDeviceAddress = address;
		ioctl(_file, I2C_SLAVE, _lastDeviceAddress); 
	}
}
//
bool i2cOpen(void){
	if(_file > 0 ) return true;
	_file = open(I2C_DEV_NAME, O_RDWR);
    if (_file == -1)
		return false;
	_lastDeviceAddress = 0;
	return true;	
}

void i2cClose(void){
	close(_file);
	_file = 0;
}

bool i2cWrite(int address, void *data_wr, size_t size)
{
	i2cOpen();
	_setAddress(address);
	return (write(_file,data_wr, size) == size);
}
 
bool i2cRead(int address, void *data_rd, size_t size)
{
	i2cOpen();
	_setAddress(address);
	return (read(_file,data_rd, size) == size);
}

bool i2cWriteCheck(int address, uint8_t byte_wr){
    bool result;
    uint8_t br;
    result = false;
	
	i2cOpen();
	_setAddress(address);
	result = false;
    for(int retry =0; retry < I2C_RETRY_COUNT;retry++) {
		if(write(_file, byte_wr, 1) == 1) {
            result = true;break;
        }
		usleep(I2C_RETRY_TIMEOUT);
    }
    if(!result) return false;
    for(int retry =0; retry < I2C_RETRY_COUNT;retry++) {
		if(read(_file,br, 1) != 1) {
			usleep(I2C_RETRY_TIMEOUT);
			continue;
		}
		if(br == byte_wr) return true;
		usleep(I2C_RETRY_TIMEOUT);
    }    
    return false;    
}

