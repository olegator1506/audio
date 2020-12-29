#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/time.h>
#include <wiringPi.h>


// Use GPIO Pin 17, which is Pin 0 for wiringPi library

#define BUTTON_PIN 0
struct timeval tvStart,tvEnd;
volatile  unsigned long diff;

// the event counter 
volatile int eventCounter = 0;


// -------------------------------------------------------------------------
// myInterrupt:  called every time an event occurs
void myInterrupt(void) {
   if(digitalRead(BUTTON_PIN) == 0) { // отрицательный фронт - начало импульса
	gettimeofday(&tvStart,NULL);
   } else {    
	gettimeofday(&tvEnd,NULL);
	diff = ((tvEnd.tv_sec - tvStart.tv_sec) * 1e06) + tvEnd.tv_usec - tvStart.tv_usec;
   }         

}


// -------------------------------------------------------------------------
// main
int main(void) {
  // sets up the wiringPi library
  if (wiringPiSetup () < 0) {
      fprintf (stderr, "Unable to setup wiringPi: %s\n", strerror (errno));
      return 1;
  }

  // set Pin 17/0 generate an interrupt on high-to-low transitions
  // and attach myInterrupt() to the interrupt
  if ( wiringPiISR (BUTTON_PIN, INT_EDGE_BOTH, &myInterrupt) < 0 ) {
      fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno));
      return 1;
  }

  // display counter value every second.
  while ( 1 ) {
    printf( "%lu\n", diff );
//    eventCounter = 0;
    delay( 1000 ); // wait 1 second
  }

  return 0;
}
