#ifndef __CONFIG_H__
#define __CONFIG_H__
// WiFi
//#define WIFI_SSID "SweetHome"
#define WIFI_SSID "AndroidAP_4239"
#define WIFI_PASSWORD "DoYr1941?"
// I2c
#define I2C_SDA_PIN 18
#define I2C_SCL_PIN 19
#define I2C_FR 100000L
#define I2C_PORT_NUM 0
#define I2C_TIMEOUT 1000
// I2c chip addresses
#define I2C_ADDRESS_ADAU 0x38
//Bluetooth
#define BT_DEV_NAME "ESP_ADAU"
// i2S output
#define I2S_BCK_PIN 26
#define I2S_DATA_PIN 22
#define I2S_LRCK_PIN 25
// MP3 module
#define MP3_TXD_PIN 33 
#define MP3_RXD_PIN 32
// OTA
#define OTA_UPGRADE_URL "http://192.168.43.82/audio/progs/esp32-adau/.pio/build/esp-wrover-kit/firmware.bin"

#endif