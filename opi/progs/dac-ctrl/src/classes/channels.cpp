#include <string>
#include <iostream>
#include <time.h>
#include <jsoncpp/json/json.h>
#include "log/log.h"
#include "pcf/pcf.h"
#include "adau17x/adau17x.h"
#include "channels.h"



TChannel::TChannel(const char *name){
	_name = name;
	_selected = false;
	_typeString = "";
	DBG(_tag,"Construct %s", name);

};

Json::Value TChannel::getStateJson(){
	_jsonState.clear();
	_jsonState["name"]=_name;
	_jsonState["type"]=_typeString;
	_jsonState["selected"]=_selected;
	return _jsonState;
}


TAuxChannel::TAuxChannel(const char *name, int inputNum) : TChannel(name)
{
	_tag = "AuxChannel";
	_auxNum = inputNum;
	_typeString = "aux";
}	

void TAuxChannel::select(void) {
	adauI2sOff();
	pcfSelAnalogInput(_auxNum);
	TChannel::select();
}

// Класс TDiffChannel
TDiffChannel::TDiffChannel(const char *name) : TChannel(name)
{
	_tag = "DiffChannel";
	_typeString = "line";
}	
void TDiffChannel::select(void) {
	adauI2sOff();
	TChannel::select();
}

// Класс TAlsaChannel
TAlsaChannel::TAlsaChannel(const char *name) : TChannel(name)
{
	_tag = "AlsaChannel";
	_typeString = "file";
}

void TAlsaChannel::select(void)
{
	DBG(_tag,"select");
	adauI2sOn();
	adauI2sGain(0.5);
}
	


    