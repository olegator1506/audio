#include <string.h>
#include "channels.h"
#include "mongoose/mongoose.h"
#include "adau17x/adau17x.h"

static const char *__labels[EQ_TOTAL_CHANNELS] = EQ_LABELS;
static const int _eqPpresets[4][EQ_TOTAL_CHANNELS] = {
	{0,0,0,0,0,0}, // reset
	{5,3,1,0,1,2}, //Jazz
	{0,0,0,0,0,0}, // Rock
	{0,0,0,0,0,0}, // classic
};
DacCtrl::DacCtrl(void){
    for(int i=0; i< EQ_TOTAL_CHANNELS;i++)
		_eqLabels[i] = __labels[i];
	_eqReset();
	_bass = false;
	_dspEnabled = true;
}

void DacCtrl::_eqSetBandValue(int band, int value){
	if((band <0) || (band >= EQ_TOTAL_CHANNELS)) return;
	if(value == _eqValues[band]) return;
	if((value < EQ_LEVEL_MIN) || (value > EQ_LEVEL_MAX)) return;
	_eqValues[band] = value;
	adauEqSet(band, value);
}

bool DacCtrl::_eqPreset(const struct mg_str *query) {
	char arg[20];
   	if(mg_get_http_var(query,"mode",arg,20) <= 0) return false;
	int mode = atoi(arg);
	if ((mode <0) || (mode > 3)) return false;
	const int *values = _eqPpresets[mode];
	for(int i=0;i<EQ_TOTAL_CHANNELS;i++) 
		_eqSetBandValue(i,values[i]);
	return true;
}

void DacCtrl::_eqReset(void){
	for(int i=0; i< EQ_TOTAL_CHANNELS;i++){
		_eqValues[i] = 0;
		adauEqSet(i,_eqValues[i]);
	}
}

bool DacCtrl::_eqSet(const struct mg_str *query) {
    char arg[20];
    int band, value;
   	if(mg_get_http_var(query,"band",arg,20) <= 0) return false;
    band = atoi(arg);
    if((band <0) || (band >= EQ_TOTAL_CHANNELS)) return false;
    if(mg_get_http_var(query,"value",arg,20) <= 0) return false;
    value = atoi(arg);
    if((value < EQ_LEVEL_MIN) || (value > EQ_LEVEL_MAX)) return false;
    _eqValues[band] = value;
    adauEqSet(band,value);
	return true;
} 

void DacCtrl::_setBass(bool state){
	if(state == _bass) return;
	_bass = state;
	adauSuperBass(state);
}

bool DacCtrl::_setBass(const struct mg_str *query) {
    char arg[20];
    bool value;
   	if(mg_get_http_var(query,"state",arg,20) <= 0) return false;
	if(strcmp(arg,"on") == 0)    value = true;
	else if(strcmp(arg,"off") == 0)    value = false;
	else return false;
	_setBass(value);
	return true;
}

bool DacCtrl::runCommand(const struct mg_str *query){
    char op[255];
    snprintf(lastError, 1023, "Invalid request: one or more parameters not specified or invaalid");
	if(mg_get_http_var(query,"op",op,255) <= 0) return false;
    if(strcmp(op,"set_eq") == 0) return _eqSet(query);
	if(strcmp(op,"bass") == 0) return _setBass(query);
	if(strcmp(op,"state") == 0) return true;
	if(strcmp(op,"eq_preset") == 0) return _eqPreset(query);
	return false;
}

Json::Value DacCtrl::getStateJson(){
	_jsonState.clear();
	_jsonState["eq_band_count"]= EQ_TOTAL_CHANNELS;
	_jsonState["eq_min_value"]= EQ_LEVEL_MIN;
	_jsonState["eq_max_value"]= EQ_LEVEL_MAX;
	Json::Value labels,values;
	for(int i=0; i< EQ_TOTAL_CHANNELS;i++){
		labels.append(_eqLabels[i]);
		values.append(_eqValues[i]);
	}
	_jsonState["eq_labels"]= labels;
	_jsonState["eq_values"]= values;
	_jsonState["bass"]= _bass;
	_jsonState["dsp"]= _dspEnabled;
	return _jsonState;
}

DacCtrl *dac;

