#include "selector.h"
#include "log/log.h"
#include "adau17x/adau17x.h"

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
    },
    { // Линейный дифференциальный вход
        .type = CH_TYPE_ALSA,
        .name = "ALSA",
        .auxNum = 0,
    },

	
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
			}
	_selectedChNum = 0;		
	_channels[_selectedChNum]->select();
}
void TSelector::select(int chNum, bool force){
	if((chNum >= TOTAL_CHANNELS) || (chNum < 0)) {
		LOGE(_tag,"Invalid channel number %d",chNum);
	}
	DBG(_tag,"Select channel #%d",chNum); 
	if((chNum == _selectedChNum) && !force) return;
	if(chNum != _selectedChNum)
	    _channels[_selectedChNum]->unselect(); 
	_selectedChNum = chNum;
	_channels[_selectedChNum]->select(); 
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
	return adauEqSet(band, value);
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
	return _jsonState;	
}
TSelector *Selector;
