#include "driver/i2c.h"

static int _timeout = 0,_portNum;
esp_err_t i2cWrite(uint8_t address,uint8_t *data_wr, size_t size)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (address << 1) , 1);
    i2c_master_write(cmd, data_wr, size, 1);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(_portNum, cmd, _timeout / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    return ret;
}
 
esp_err_t i2cRead(uint8_t address, uint8_t *data_rd, size_t size)
{
    if (size == 0) {
        return ESP_OK;
    }
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (address << 1) | 1, 1);
    if (size > 1) {
        i2c_master_read(cmd, data_rd, size - 1, 0);
    }
    i2c_master_read_byte(cmd, data_rd + size - 1, 1);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(_portNum, cmd, _timeout / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    return ret;
}


esp_err_t i2cInit(int portNum, int sdaPin,int sclPin,unsigned long frequency,int timeout){
    _timeout = timeout;
    _portNum = portNum;
    int i2c_master_port = portNum;
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = sdaPin;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_io_num = sclPin;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = frequency;
    i2c_param_config(i2c_master_port, &conf);
    return i2c_driver_install(i2c_master_port, conf.mode,0,0,0);
}