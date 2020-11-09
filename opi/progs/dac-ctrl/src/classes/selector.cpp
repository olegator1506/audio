#include <stdio.h>
#include <string.h>
#include <string>
#include "selector.h"
#include "log/log.h"
#include "adau17x/adau17x.h"
#include "adau17x/projects/project4_IC_2_PARAM.h"
#include "channels.h"
#include "playlist.h"

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

    { // AUX #3 разъем на задней панели
        .type = CH_TYPE_AUX,
        .name = "AUX3",
        .auxNum = 3,
    },
    { // Воспроизведение файлов через AlsaPlayer
        .type = CH_TYPE_ALSA,
        .name = "ALSA",
        .auxNum = 0, // not used
    },


    { // MPD
        .type = CH_TYPE_MPD,
        .name = "MPD",
        .auxNum = 0, // not used
    },

    { // Воспроизведение аудиопотока Spotify
        .type = CH_TYPE_SPOTIFY,
        .name = "SPOTIFY",
        .auxNum = 0 // not used
    }

};



// Класс TSelector 
 TSelector::TSelector(void){
	 _tag = "Selector";
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
			case CH_TYPE_SPOTIFY:
				_channels[i] = new TSpotify(_channelsConfig[i].name);
				break;
			case CH_TYPE_MPD:
				_channels[i] = new TMpdChannel(_channelsConfig[i].name);
				break;
		}
	_selectedChNum = 0;		
	_channels[_selectedChNum]->select();
	_superBass = false;
	_mute = false;
	playList = new PlayList();
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
/*
bool TSelector::setEq(int band, int value){
	DBG(_tag,"Set equakizer band %d = %d",band,value);
	if(!Eq->set(band, value)) {
		strcpy(_errorMessage,Eq->lastError());
		return false;
	}
	return true;
}
*/ 
 bool TSelector::reload(void){
	if(!adauLoadProgram()) return false;
	select(_selectedChNum,true);
	return true;
}
bool TSelector::eqReset(void) {
	return adauEqReset();
}

Json::Value TSelector::getStateJson(void){
	unsigned  i;
	_jsonState.clear();
	Json::Value channels;
	Json::Value pl;
	
	for(i=0;i<TOTAL_CHANNELS;i++)
		channels.append(_channels[i]->getStateJson());
	for(i=0;i< playList->listNames.size();i++) {
		std::string name = playList->listNames[i];
		pl.append(name);
	}
	_jsonState["channels"] = channels;	
	_jsonState["play_lists"] = pl;	
	_jsonState["selected_channel_num"] = _selectedChNum;
	_jsonState["mute"] = _mute;
	return _jsonState;	
}

bool TSelector::mute(bool value, bool force) {
	uint8_t param[4] = {0,0,0,0};
  if((_mute == value) && !force) return true;
  if(!value) param[1] = 0x80;
  DBG(_tag,"Mute %s",value ? "ON":"OFF");
  adauWrite(MOD_MUTE1_ALG1_MUTENOSLEWALG2MUTE_ADDR,param,4);
  adauWrite(MOD_MUTE1_ALG0_MUTENOSLEWALG1MUTE_ADDR,param,4);
  _mute = value;
  return true;	
}


bool TSelector::superBass(bool state) {
	if(!adauSuperBass(state)) return false;
	_superBass = state;
	return true;
}

TSelector *Selector;
