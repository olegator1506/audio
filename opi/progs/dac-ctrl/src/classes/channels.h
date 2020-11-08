#ifndef _CHANNELS_H_
#define _CHANNELS_H_
#include <string>
#include <jsoncpp/json/json.h>
#include "mongoose/mongoose.h"
#include "config.h"

#define TOTAL_CHANNELS 5

typedef enum {
    CH_TYPE_AUX, // Дополнительные входы ( один на передней панели и два на задней
	CH_TYPE_LINEIN, // Дифференциальный вход
    CH_TYPE_ALSA, // Воспроизведение файлов через AlsaPlayer
		CH_TYPE_SPOTIFY,
//    CH_TYPE_BLUETOOTH,
//    CH_TYPE_INET_RADIO,
} TChannelType;

typedef struct {
	std::string 
		path,
		title,
		genre,
		artist,
		album,
		year;
} TrackInfo;

extern TrackInfo trackInfo;

typedef struct {
	std::vector<std::string> trackList;
	bool isPlaying;
	bool isPaused;
	int curTrackNum;
	int curLength;
	int curPosition;
	std::string trackTitle,trackArtist, trackAlbum;
	int trackYear;
} PlayerStatus;

extern PlayerStatus playerStatus;



class DacCtrl {
protected:
	char *_tag;
	int _eqValues[EQ_TOTAL_CHANNELS],__inputGain;
	const char *_eqLabels[EQ_TOTAL_CHANNELS];
	bool _bass, _dspEnabled;

	Json::Value _jsonState;
	void _changeByteOrder(int32_t value, uint8_t *dst);
	bool _eqSet(const struct mg_str *query);
	void _eqReset(void);
	void _setBass(bool state, bool force = false);
	bool _setBass(const struct mg_str *query);
	void _eqSetBandValue(int band, int value, bool force = false);
	bool _eqPreset(const struct mg_str *query);
	bool _dspSwitch(const struct mg_str *query);
	bool _dspSwitch(bool value, bool force = false);
	bool _inputGain(const struct mg_str *query);
	bool _inputGain(int value, bool force = false );
public:
	char lastError[1024];
	DacCtrl(void);
	bool runCommand(const struct mg_str *query);
	Json::Value getStateJson(void);
	void apply(void);
};


class Player {
public:
	Player(void){}
	virtual bool updateStatus(void) = 0;
	virtual bool runCommand(const char *cmd, const char *arg) = 0;
	virtual void saveState(void) = 0;
	virtual void restoreState(void) = 0;
protected:
	virtual bool _loadPlayList(const char *listFileName) = 0;
	virtual bool _clearPlayList(void) = 0;

};
//////////// Объявления классов каналов /////////////////////
// Базовый класс для управления каналом
class TChannel {
protected:
		const char *_tag;
		const char *_typeString;
		std::string _name;
		bool _selected;
		Json::Value _jsonState;
		int _checkProcessRun(const char *fname);// Вертает ID процесса из файла fname если он запущен, иначе 0

public:
	Player *player;
	DacCtrl *dac;
	TChannel(const char *name);
	virtual void select(void); 
	virtual void unselect(void) {_selected = false;}
	virtual Json::Value getStateJson();
};

// Аналоговый канал (AUX вход
class TAuxChannel : public TChannel {
protected:
	int _auxNum;
	int _gain;
public:
	TAuxChannel(const char *name, int inputNum, int gain);
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
	bool _start(void);
	bool _stop(void);
	void _initPlayList(void);
public:
	TAlsaChannel(const char *name);
 	void select(void);
	void unselect(void);
	
};

class TSpotify : public TChannel {
	protected:
	bool _start(void);
	bool _stop(void);
	public:
		TSpotify(const char *name);
		void select();
		void unselect();
};



#endif