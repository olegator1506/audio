#ifndef _CHANNELS_H_
#define _CHANNELS_H_
#include <string>
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
		const char *_typeString;
		std::string _name;
		bool _selected;
		Json::Value _jsonState;

public:
	TChannel(const char *name);
	virtual void select(void) {_selected = true;}
	virtual void unselect(void) {_selected = false;}
	virtual Json::Value getStateJson();
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



#endif