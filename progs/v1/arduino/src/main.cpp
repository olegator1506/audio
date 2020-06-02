#include <Arduino.h>
#include <TimerOne.h>
#include <RotaryEncoder.h>
//#include "commands.h"
#include "irmp.h"
#include "config.h"
#include "debug.h"

const int chSelPins[3] = CH_SEL_PINS;


RotaryEncoder encoder(ENCODER_PINS);



uint32_t vuSumms[2] = {0,0};
int vuCnt = 0;
bool vuReady = false;
int _vuGetVal(int pin) {
  int res = analogRead(pin);
  if(res <VU_MUTE_VAL) res = 0;
  else res -= VU_MUTE_VAL;
  return res;
}

void timerVuHandler(void){
  if(vuReady) return;
    vuSumms[VU_CH_LEFT] += _vuGetVal(VU_PIN_LEFT);
    vuSumms[VU_CH_RIGHT] += _vuGetVal(VU_PIN_RIGHT);
    vuCnt++;
    if(vuCnt == VU_CNT) {
      vuReady = true;
    }
}
void vuLoop(void){
  float vals[2];
  if(!vuReady) return;
  for(int i=0;i<2;i++) {
    vals[i] = vuSumms[i] / vuCnt;
    Serial.print("Left ");Serial.print(vals[0]);Serial.print(" Right ");Serial.println(vals[1]);
    vuSumms[i] = 0;
  }
  vuReady = false;
  vuCnt =0;
}
void timer_handle_interrupts(void) {
    irmp_ISR(); 
//    timerVuHandler();
}

void IrLoop(void){
    IRMP_DATA data;
    static unsigned long lastTime=0;
    if (!irmp_get_data(&data)) return;
    unsigned long t = millis();
    if((t - lastTime) < 200) return;
    lastTime = t;
    DBG(F("IR code %02X"),data.command);
    DBG(F("IR protocol %02X"),data.protocol);
   Serial.write(data.command);
}

static void selectOutput(uint8_t num) {
    for(uint8_t i=0;i<3;i++) {
        digitalWrite(chSelPins[i],(num & (1<<i)) ? 1 :0);
    }    
}

void encoderLoop(){
  static int pos = 0;
  uint8_t cmd = 0;
  encoder.tick();
  int newPos = encoder.getPosition();
  if (pos == newPos) return;
  cmd = (pos < newPos) ? CMD_ECODER_PLUS : CMD_ECODER_MINUS;
  pos = newPos;
  Serial.write(cmd);
}
/*
void _powerOff(void){
  DBG(F("Power Off"));
  digitalWrite(PIN_PWR_AMP,1);// Выключаем питание усилителя
  delay(10);
  digitalWrite(PIN_PWR,0); // Включаем питание аналогового модуля
}
void _powerOn(void){
  DBG(F("Power On"));
  digitalWrite(PIN_PWR,1); // Включаем питание аналогового модуля
  delay(10);
  digitalWrite(PIN_PWR_AMP,0);// Включаем питание усилителя
}
*/
void _powerBits(uint8_t b) {
  int pins[] = PINS_PWR;
  for(int i = 0; i < 4; i++) {
    if(pins[i] == -1) continue;
    digitalWrite(pins[i], (b & (1 <<i)) ? 1 :0);
  }
}

void uartLoop(){
  if(Serial.available() == 0) return;
  uint8_t b = Serial.read();
  uint8_t cmd = b >> 4; // старшие 4 бита определяют команду
  switch(cmd) {
    case 0:// Выбор номера аанлогового выхода
      selectOutput(b & 0x7);
      break;
    case 1: // ping
      Serial.write(b); // отправляем обратно
      break;
    case 2: // управление питанием
/*
      int onoff = b & 1;
      if(onoff)  _powerOn();
        else    _powerOff();
*/
      _powerBits( b & 0x07);
      break;  
  }
}

void setup() {
  Serial.begin(115200);
  while(!Serial);
#ifdef __DEBUG__  
  debugMode = true;
#ifdef DEBUG_SERIAL  
  debugSerial = true;
#else 
  debugSerial = false;
#endif
#endif  
//  pinMode(VU_PIN_LEFT,INPUT);
//  pinMode(VU_PIN_RIGHT,INPUT);
//  pinMode(PIN_PWR,OUTPUT);
//  pinMode(PIN_PWR_AMP,OUTPUT);
//  pinMode(PIN_MUTE,OUTPUT);
//  digitalWrite(PIN_PWR,0); // питание аналогового модуля выкл
//  digitalWrite(PIN_PWR_AMP,1);// питание аналогового модуля выкл
//  digitalWrite(PIN_MUTE,0); // Выход усилителя выкл
  Timer1.initialize(TIMER_PERIOD);
  Timer1.attachInterrupt(timer_handle_interrupts);
  int b[] = PINS_PWR;
  for(int i=0;i<4;i++)
    if(b[i] != -1) pinMode(b[i],OUTPUT);

  for(int i=0;i<3;i++)
    pinMode(chSelPins[i],OUTPUT);
//  for(int i=0;i<2;i++)    pinMode(encoderPins[i],INPUT_PULLUP);

  irmp_init(); // Start IR receiver
  _powerBits(0);
  
}
void loop() {
    IrLoop();
//    vuLoop();
  uartLoop();
  encoderLoop();
}