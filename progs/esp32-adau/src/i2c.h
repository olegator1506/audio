#ifndef __I2C_H__
#define __I2C_H__
#include <esp_err.h>
extern esp_err_t i2cInit(void);
extern esp_err_t i2cRead(uint8_t address, uint8_t *data_rd, size_t size);
extern esp_err_t i2cWrite(uint8_t address,uint8_t *data_wr, size_t size);
#endif
