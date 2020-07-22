#ifndef __CONFIG_H__
#define __CONFIG_H__
// WiFi
#define WIFI_SSID "SweetHome"
#define WIFI_PASSWORD "DoYr1941?"
// I2c
#define I2C_SDA_PIN 19
#define I2C_SCL_PIN 18
#define I2C_FR 100000L
#define I2C_PORT_NUM 0
#define I2C_TIMEOUT 1000
// I2c chip addresses
#define I2C_ADDRESS_ADAU 0x38
// MP3 module connection
//#define MP3_TXD_PIN (GPIO_NUM_32)
//#define MP3_RXD_PIN (GPIO_NUM_33)
#define MP3_TXD_PIN 33
#define MP3_RXD_PIN 32

#endif 