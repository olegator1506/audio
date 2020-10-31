#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "include/alsa.h"
int count = 0;

void *start(void *param){
    int i, upper = atoi((const char *)param);
    count = 0;
    printf("Thread start\n");  
    if (upper > 0) {
        for (i = 1; i <= upper; i++)
            count += i;
    }
    printf("Thread end\n");  
    pthread_exit(0);    
 }

void help(void){
    perror("tone <sound_device_name> <sample_rate> <frequency> <amplitude> <form>\nForm = meandr | sinus\n");
    exit(1);
}

int main(int argc, char **argv){
    int frequency, rate, amplitude;
    char *deviceName = argv[1], *form = argv[5];
    if(argc != 6) help();
    rate = atoi(argv[2]);
    frequency = atoi(argv[3]);
    if((frequency < 1) || (frequency > 20000)) {
        perror("Invalid frequency value. Valid range is 1..20 000\n");
        help();
    }
    amplitude = atoi(argv[4]);
    if((amplitude < 1) || (amplitude > 65535)) {
        perror("Invalid amplitude value. Valid range is 1..65535 000\n");
        help();
    }
    printf("Sample rate = %d Frequency = %d \n",_actualRate, frequency);
    if(!alsaInit(deviceName, rate)) exit(1);
    if(strcmp(form,"sinus") == 0)
        sinus(frequency,amplitude);
    else if(strcmp(form,"meandr")==0)
        meandr(frequency,amplitude);
    else {
        perror("Invalid form value. Must be \"meandr\" or \"sinus\"\n");
        help();
    }    
    
}