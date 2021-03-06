#ifndef __I2C_H__
#define __I2C_H__
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
extern bool i2cOpen(void);
extern void i2cClose(void);
extern bool i2cWrite(int address, void *data_wr, size_t size);
extern bool i2cRead(int address, void *data_wr, size_t size);
extern bool i2cWriteCheck(int address, uint8_t byte_wr);
#endif
