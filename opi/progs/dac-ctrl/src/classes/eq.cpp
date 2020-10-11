#include <stdio.h>
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
bool  TEq::set(int band, int value){
	if((band < 0) || (band >= EQ_TOTAL_CHANNELS)) {
		snprintf(_errorMessage,255,"Eq invalid band number %d",band);
		return false;
	}
	if((value < EQ_LEVEL_MIN) || (value > EQ_LEVEL_MAX)) {
		snprintf(_errorMessage,255,"Eq invalid value %d",value);
		return false;
	}
	
	_values[band] = value;
	adauEqSet(band,value);
	return true;
}

Json::Value TEq::getStateJson(){
	_jsonState.clear();
	_jsonState["band_count"]= EQ_TOTAL_CHANNELS;
	_jsonState["min_value"]= EQ_LEVEL_MIN;
	_jsonState["max_value"]= EQ_LEVEL_MAX;
	Json::Value labels,values;
	for(int i=0; i< EQ_TOTAL_CHANNELS;i++){
		labels.append(_labels[i]);
		values.append(_values[i]);
	}
	_jsonState["labels"]= labels;
	_jsonState["values"]= values;
	return _jsonState;
}

TEq *Eq;