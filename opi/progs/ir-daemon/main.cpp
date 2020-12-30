#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <wiringPi.h>


// Use GPIO Pin 17, which is Pin 0 for wiringPi library

#define BUTTON_PIN 0
#define TIME_PREAMBLE 13500
#define TIME_ZERO 1125
#define TIME_ONE 2250
#define TIME_REPEAT 11250
#define TIME_ERROR 100
#define FRAME_TIMEOUT 100000L
#define PULSE_TIMEOUT 20000L

unsigned char address,command;
typedef enum {PULSE_PREAMBLE,PULSE_ZERO,PULSE_ONE,PULSE_REPEAT,PULSE_ERROR} PulseType;

static struct timeval _lastPulseTime = {0,0}; // время последнего отрицаельного фронта
static volatile int  _bitNum; // текущий ноамер принятого бита
u_int32_t _resultVal;// Результирующее значение
static bool _started; //признак начала приема пакета(принят импульс-преамбула)
static bool _paused = true; // прием приостановлен 
static bool _ready = false;
static char _errMess[1024];
// the event counter 
volatile int eventCounter = 0;


static void _reset(void){
	_started = false;
  _bitNum = 0;
  _resultVal = 0L;
  _ready = false;
}

static unsigned long _timeDiff(struct timeval from, struct timeval to) {
 return ((to.tv_sec - from.tv_sec) * 1000000L) + to.tv_usec - from.tv_usec;
}

static PulseType _pulseType(unsigned long t){
  if(t > (TIME_PREAMBLE + TIME_ERROR)) return PULSE_ERROR;
  if( (t >= (TIME_PREAMBLE - TIME_ERROR)) && (t <= (TIME_PREAMBLE + TIME_ERROR))) return PULSE_PREAMBLE;
  if( (t >= (TIME_ZERO - TIME_ERROR)) && (t <= (TIME_ZERO + TIME_ERROR))) return PULSE_ZERO;
  if( (t >= (TIME_ONE - TIME_ERROR)) && (t <= (TIME_ONE + TIME_ERROR))) return PULSE_ONE;
  if( (t >= (TIME_REPEAT - TIME_ERROR)) && (t <= (TIME_REPEAT + TIME_ERROR))) return PULSE_REPEAT;
  return PULSE_ERROR;
}
/*
static bool _inInterval(unsigned long t, unsigned long interval) {
  unsigned long min = interval - TIME_ERROR;
  unsigned long max = interval + TIME_ERROR;
  return ((t >= min) && (t <= max));
}
*/

static unsigned long _savePulse(void){
  struct timeval t;
  unsigned long diff;
	gettimeofday(&t,NULL);
  if((_lastPulseTime.tv_sec == 0) && (_lastPulseTime.tv_usec == 0)) {// Первый импульс
    _lastPulseTime = t; 
    return 0;
  }
  diff = _timeDiff(_lastPulseTime, t);
  if(diff > PULSE_TIMEOUT) { // Длительность больше длины пакета, считаем что это новый пакет
   _reset();
   _lastPulseTime = t; 
   return 0;
  }
  _lastPulseTime = t;
  return diff;
}

void _pause() {
  _paused = true;
}

void _resume() {
  _reset();
  _paused = false;
  _errMess[0] = '\0';
}

void _error(char *mess, unsigned long t){
  snprintf(_errMess,1023,"%s Pulse %lu us bitNum= %d started %s",mess,t,_bitNum, _started ? "Yes":"No");
  _pause();
}

// -------------------------------------------------------------------------
// myInterrupt:  called every time an event occurs
void _myInterrupt(void) {
  if(_paused) return;
  if(_ready) return; // Пакет принят но не обработан, прием отключен
  unsigned long diff = _savePulse();
  if(diff == 0) return; 
  PulseType pulseType = _pulseType(diff);
  switch(pulseType) {
    case PULSE_ERROR:
      _error("Invalid pulse duration",diff);
      break;
    case PULSE_REPEAT:
      break;
    case PULSE_PREAMBLE:
      if(!_started) {
        _started = true;
        _bitNum = 0;
      } else _error("Preamble pulse during bit receiving",diff);
      break;
    case PULSE_ZERO:
    case PULSE_ONE:
      if(_started) {
        _resultVal = _resultVal<< 1;
        if(pulseType == PULSE_ONE) _resultVal++; 
        _bitNum++;
	if(_bitNum == 32) {
	    _pause();
	    unsigned char b[4];
	    b[0] = _resultVal & 0xff;
	    b[1] = (_resultVal>>8) & 0xff;
	    b[2] = (_resultVal>>16) & 0xff;
	    b[3] = (_resultVal>>24) & 0xff;
	    if(((b[0] ^ b[1]) != 0xff) || ((b[2] ^ b[3]) != 0xff))
		_error("Invalid command bytes",0);

	}
      } else _error("Bit pulse before preamble",diff);      
  }
}

void check(void) {
  if(strlen(_errMess)) {
    printf("ERROR: %s\n",_errMess);
    exit(1);
  }
}


void emulate(void){
  unsigned long val = 0xf00fa55a;
  _resume();
// Преамбула
  _myInterrupt();
  check();
  usleep(TIME_PREAMBLE);
  _myInterrupt();
  check();
  for(int i = 0;i < 32;i++) {
    if(val & (1<<i)) usleep(TIME_ONE);
    else usleep(TIME_ZERO);
    _myInterrupt();
    check();
  }
  usleep(TIME_ZERO);
  _myInterrupt();
  check();
  if(_resultVal != val) 
    printf("data not equal send %X receive %X\n",val,_resultVal);
  printf("Ok\n");
}

// -------------------------------------------------------------------------
// main
int main(void) {
  // sets up the wiringPi library
  if (wiringPiSetup () < 0) {
      fprintf (stderr, "Unable to setup wiringPi: %s\n", strerror (errno));
      return 1;
  }
  if ( wiringPiISR (BUTTON_PIN, INT_EDGE_FALLING, &_myInterrupt) < 0 ) {
      fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno));
      return 1;
  }
  while(1){
    _resume();
    while(!_paused);
    if(strlen(_errMess)) 
	printf("ERROR: %s\n",_errMess);
    else {
	unsigned char b[4];
	b[0] = _resultVal & 0xff;
	b[1] = (_resultVal>>8) & 0xff;
	b[2] = (_resultVal>>16) & 0xff;
	b[3] = (_resultVal>>24) & 0xff;
	if(((b[0] ^ b[1]) != 0xff) || ((b[2] ^ b[3]) != 0xff))
    	    printf("Invalid data received %08X",_resultVal);
	else {
	    address = b[3];
	    command = b[1];
	    printf("Got value  %08X -> %02X:%02X\n",_resultVal,address,command);
	}	    
    }
            	
  }          

}
