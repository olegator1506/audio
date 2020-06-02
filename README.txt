Контакты ESP32 (по назначению):
   TFT дисплей ST7735
IO_23 TFT SDA
IO_19 TFT SCK
IO_2  TFT CS
IO_21 TFT A0

====  I2S ==========
IO_26 BCK
IO_22 LRCK 
IO_25 DATA  

=== I2c (связь с ADAU и PCF8574)
IO_5 SDA
IO_17 SCL

---  MP3 модуль ---
IO_16  MP3_TXD -> MP3 RxD
IO_4  MP3_RXD -> MP3 TxD

-- Управление коммутатором каналов
IO_14 ChSel0
IO_12 ChSel1

--- Входы
IO_32 Аналоговый вход опроса состояния регуляторов
IO_18 Вход IR датчика ДУ
Sensor_VP Enc1
Sensor_VN Enc2


Звуковые входы (CD4052)
0 AUX1
1 AUX2
2 MP3
3 FM

Разъем фронтальной платы
1 Vcc
2 Gnd
3 EncA
4 EncB
5 SDA
6 SCL
7 Volume
8 -
