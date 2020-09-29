#include <stdio.h>
#include <stdlib.h>
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

int main(int argc, char **argv){
    int duration, rate;
/*     pthread_t tid;
    pthread_attr_t attr;
    printf("main program  started\n");
    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, start,argv[1]);
    pthread_join(tid,NULL);
    printf("count = %d\n",count);
 */    
    rate = atoi(argv[2]);
    duration = argv[3] ? atoi(argv[3]) : 0;
    if(duration < 0) duration = 0;  
    printf("Sample rate %d Duration %d seconds\n",rate, duration);
    if(!alsaInit(argv[1], rate)) exit(1);
    alsaGenSound(duration);
}