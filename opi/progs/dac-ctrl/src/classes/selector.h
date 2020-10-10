#ifndef __SELECTOR_H__
#define __SELECTOR_H__

#include "channels.h"

class TSelector {
protected:
	int _selectedChNum; 
	TChannel *_channels[TOTAL_CHANNELS];
	const char *_tag; 
	Json::Value _jsonState;
public:
	TSelector();
//	char *errorMessaage;
//	bool error(const char *message);
	void selectNext();
	void selectPrev();
	void select(int chNum, bool force = false);
//	bool unselect(int);
//	bool isAvailable(int chNum);
//	int count(void);
	bool setEq(int band, int value);
	bool reload(void);
	bool eqReset(void);
	Json::Value getStateJson(void);
/*
    channelsEventHandler(uint8_t code,uint16_t param);
	bool play(void);
	int nextTrack(void);
	int prevTrack(void);
	int selectFolder(int);
extern bool nextFolder(void);
extern esp_err_t channelPrevFolder(void);
extern esp_err_t channelPause(void);
extern esp_err_t channelResume(void);
extern esp_err_t channelSwitchPause(void);
extern esp_err_t channelStop(void);
extern esp_err_t channelVolume(int volume);
extern esp_err_t channelEqualizer(int volume);
extern void channelBtState(bool state);
extern void channelBtSetAttr(int attrId, char *attrText);
 esp_err_t channelSwitchPause(void);
*/	
};
extern TSelector *Selector;

#endif