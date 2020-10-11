#include "config.h"
#include "eq.h"
#include "adau17x/adau17x.h"

static const char *__labels[EQ_TOTAL_CHANNELS] = EQ_LABELS;


TEq::TEq(void){
	for(int i=0; i< EQ_TOTAL_CHANNELS;i++)
		_labels[i] = __labels[i];
	reset();
}
void TEq::reset(){
	for(int i=0; i< EQ_TOTAL_CHANNELS;i++){
		_values[i] = 0;
		adauEqSet(i,_values[i]);
	}
	
}
void TEq::set(int band, int value){
	_values[band] = value;
	adauEqSet(band,value);
}

TEq *Eq;