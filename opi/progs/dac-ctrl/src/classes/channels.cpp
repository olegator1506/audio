#include <string>
#include <iostream>
#include <time.h>
#include "log/log.h"
#include "pcf/pcf.h"
#include "adau17x/adau17x.h"
#include "channels.h"



typedef struct {
    TChannelType type; 
    const char *name;//Символьное имя канала
	int auxNum; // номер аудио выхода устройства (на выходном аналоговом коммутаторе)
} TChannelConfig;


static TChannelConfig _channelsConfig[TOTAL_CHANNELS] = {
    { // AUX #1 разъем на фронтальной панели
        .type = CH_TYPE_AUX,
        .name = "AUX1",
        .auxNum = 1,
    },
    { // AUX #2 разъем на задней панели
        .type = CH_TYPE_AUX,
        .name = "AUX2",
        .auxNum = 2,
    },
/*
    { // AUX #2 разъем на задней панели
        .type = CH_TYPE_AUX,
        .name = "AUX3",
        .auxNum = 3,
    },
*/
    { // Линейный дифференциальный вход
        .type = CH_TYPE_LINEIN,
        .name = "LINE",
        .auxNum = 0,
    }
	
};


TChannel::TChannel(const char *name){
	_name = name;
	_selected = false;
	DBG(_tag,"Construct %s", name);

};


TAuxChannel::TAuxChannel(const char *name, int inputNum) : TChannel(name)
{
	_tag = "AuxChannel";
	_auxNum = inputNum;
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
}	
void TDiffChannel::select(void) {
	adauI2sOff();
	TChannel::select();
}

// Класс TAlsaChannel
TAlsaChannel::TAlsaChannel(const char *name) : TChannel(name)
{
	_tag = "AlsaChannel";
}

void TAlsaChannel::select(void)
{
	DBG(_tag,"select");
	adauI2sOn();
}
	


// Класс TSelector 
 TSelector::TSelector(void){
	for(int i =0; i<TOTAL_CHANNELS; i++)
		switch(_channelsConfig[i].type){
			case CH_TYPE_AUX:
				_channels[i] = new TAuxChannel(_channelsConfig[i].name, _channelsConfig[i].auxNum);
				break;
			case CH_TYPE_LINEIN:
				_channels[i] = new TDiffChannel(_channelsConfig[i].name);
				break;
			case CH_TYPE_ALSA:
				_channels[i] = new TAlsaChannel(_channelsConfig[i].name);
				break;
			}

}

TSelector *Selector;
    