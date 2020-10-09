#ifndef _CHANNELS_H_
#define _CHANNELS_H_
#include <jsoncpp/json/json.h>
#define TOTAL_CHANNELS 4

typedef enum {
    CH_TYPE_AUX, // Дополнительные входы ( один на передней панели и два на задней
	CH_TYPE_LINEIN, // Дифференциальный вход
    CH_TYPE_ALSA, // Воспроизведение файлов через AlsaPlayer
//    CH_TYPE_BLUETOOTH,
//    CH_TYPE_INET_RADIO,
} TChannelType;
//////////// Объявления классов каналов /////////////////////
// Базовый класс для управления каналом

class TChannel {
protected:
		const char *_tag;
		std::string _name;
		bool _selected;
		Json::Value _jsonState;
public:
	TChannel(const char *name);
	virtual void select(void) {_selected = true;}
	virtual void unselect(void) {_selected = false;}
	virtual Json::value getStateJson();
};

// Аналоговый канал (AUX вход
class TAuxChannel : public TChannel {
protected:
	int _auxNum;	
public:
	TAuxChannel(const char *name, int inputNum);
 	void select(void);
};

// Дифференциальный Аналоговый канал 
class TDiffChannel : public TChannel {
protected:
public:
	TDiffChannel(const char *name);
 	void select(void);
//	void unselect(void);
};

// Воспроизведение файлов через AlsaPlayer
class TAlsaChannel : public TChannel {
protected:

public:
	TAlsaChannel(const char *name);
 	void select(void);

};



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
	Json::value getStateJson();
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