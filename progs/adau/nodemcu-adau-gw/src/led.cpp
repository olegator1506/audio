#include <Arduino.h>

#define LED_PIN D4

static unsigned long _blinkStart = 0;
static unsigned _blinkDuration;

static void _led(bool state){
  digitalWrite(LED_PIN,!state);
}

void ledBlink(unsigned t) {
    _blinkStart = millis();
    _blinkDuration = t;
    _led(true);
}

void ledLoop(void) {
    if(!_blinkStart) return;
    if((millis() - _blinkStart ) >= _blinkDuration) {
        _led(false);
        _blinkStart = 0;
    }
}
void ledInit(void) {
    pinMode(LED_PIN,OUTPUT);
    _led(false);
}
