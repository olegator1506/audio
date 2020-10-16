#include <stdio.h>
#include <string.h>
#include "selector.h"
#include "log/log.h"
#include "adau17x/adau17x.h"
#include "eq.h"

typedef struct {
    TChannelType type; 
    const char *name;//Символьное имя канала
	int auxNum; // номер аудио выхода устройства (на выходном аналоговом коммутаторе)
	int gain;
} TChannelConfig;


static TChannelConfig _channelsConfig[TOTAL_CHANNELS] = {
    { // AUX #1 разъем на фронтальной панели
        .type = CH_TYPE_AUX,
        .name = "AUX1",
        .auxNum = 1,
		.gain = 5
    },
    { // AUX #2 разъем на задней панели
        .type = CH_TYPE_AUX,
        .name = "AUX2",
        .auxNum = 2,
		.gain = 5
    },

    { // AUX #2 разъем на задней панели
        .type = CH_TYPE_AUX,
        .name = "AUX3",
        .auxNum = 3,
		.gain = 5
    },
/*
    { // Линейный дифференциальный вход
        .type = CH_TYPE_LINEIN,
        .name = "LINE",
        .auxNum = 0,
    },
*/
    { // Воспроизведение файлов через AlsaPlayer
        .type = CH_TYPE_ALSA,
        .name = "ALSA",
        .auxNum = 0, // not used
		.gain = 0
    },
    { // Воспроизведение аудиопотока Spotify
        .type = CH_TYPE_SPOTIFY,
        .name = "SPOTIFY",
        .auxNum = 0, // not used
		.gain = 0 // not used
    }


	
};



// Класс TSelector 
 TSelector::TSelector(void){
	 _tag = "Selector";
	for(int i =0; i<TOTAL_CHANNELS; i++)
		switch(_channelsConfig[i].type){
			case CH_TYPE_AUX:
				_channels[i] = new TAuxChannel(_channelsConfig[i].name, _channelsConfig[i].auxNum, _channelsConfig[i].gain);
				break;
			case CH_TYPE_LINEIN:
				_channels[i] = new TDiffChannel(_channelsConfig[i].name);
				break;
			case CH_TYPE_ALSA:
				_channels[i] = new TAlsaChannel(_channelsConfig[i].name);
				break;
			case CH_TYPE_SPOTIFY:
				_channels[i] = new TSpotify(_channelsConfig[i].name);
				break;
		}
	_selectedChNum = 0;		
	_channels[_selectedChNum]->select();
	Eq = new TEq();
}
void TSelector::finish(void){
	DBG(_tag,"Selector finished");
	_channels[_selectedChNum]->unselect();
}
bool TSelector::select(int chNum, bool force){
	if((chNum >= TOTAL_CHANNELS) || (chNum < 0)) {
		LOGE(_tag,"Invalid channel number %d",chNum);
		snprintf(_errorMessage,255,"Invalid channel number %d",chNum);
		return false;
	}
	DBG(_tag,"Select channel #%d",chNum); 
	if((chNum == _selectedChNum) && !force) return true;
	if(chNum != _selectedChNum)
	    _channels[_selectedChNum]->unselect(); 
	_selectedChNum = chNum;
	_channels[_selectedChNum]->select(); 
	return true;
}
void TSelector::selectNext(void){
	int num = (_selectedChNum == (TOTAL_CHANNELS-1)) ? 0 : (_selectedChNum +1);
	select(num);
}

void TSelector::selectPrev(void){
	int num = (_selectedChNum == 0) ? (TOTAL_CHANNELS - 1) : (_selectedChNum - 1);
	select(num);
}

bool TSelector::setEq(int band, int value){
	DBG(_tag,"Set equakizer band %d = %d",band,value);
	if(!Eq->set(band, value)) {
		strcpy(_errorMessage,Eq->lastError());
		return false;
	}
	return true;
}
 bool TSelector::reload(void){
	if(!adauLoadProgram()) return false;
	select(_selectedChNum,true);
	return true;
}
bool TSelector::eqReset(void) {
	return adauEqReset();
}

Json::Value TSelector::getStateJson(void){
	_jsonState.clear();
	Json::Value channels;
	for(int i=0;i<TOTAL_CHANNELS;i++)
		channels.append(_channels[i]->getStateJson());
	_jsonState["channels"] = channels;	
	_jsonState["selected_channel_num"] = _selectedChNum;
	_jsonState["eq"] = Eq->getStateJson();
	return _jsonState;	
}

TSelector *Selector;
