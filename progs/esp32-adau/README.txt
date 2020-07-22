---------------- Проблемы ------------
- Срабатывает Brownout detector Вероятно какието проблемы с питанием, пришлось его отключить. !! Не забыть потом включить sdkconfig->ComponentConfig->ESP specific->Brown..


Используемы контакты esp32
Контакты для вывода (всего 9)
4 -18 -19 -21 -22 -23 -25 -26 -27 
i2c 12 14
TFT_LED 2

--free--   4
I2C_SDA_PIN 12
I2C_SCL_PIN 14
15
16
17
TFT_RST 18
TFT_SCK 19
TFT_A0 21
I2S_DATA_PIN 22
TFT_SDA 23
I2S_LRCK_PIN 25
I2S_BCK_PIN 26
TFT_LED 27
MP3_RXD_PIN 32
MP3_TXD_PIN 33 
DAC_PIN 34 Чтение данных с регуляторов
35(input only)
36(SVP)(input only)
39(SVN)(input only)
