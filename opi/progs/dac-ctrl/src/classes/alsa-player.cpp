#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <vector>
#include <string>
#include <alsaplayer/control.h>
#include "adau17x/adau17x.h"
#include "channels.h"
#include "config.h"



static int _sNum = -1;
std::vector<std::string> _playLists;
PlayerStatus playerStatus; 

TrackInfo trackInfo;

static int _isRunning(void){
	int ss = -1;
	int res = ap_find_session(ALSA_PLAYER_SESSION_NAME,&ss);
	if(!res) 
		return false;
	if(ss < 0) return false;
	_sNum = ss;	
	return true;
}


class TAlsaPlayer : public Player {
protected:
	PlayerStatus _savedStatus;
	bool _saved ;
	bool _loadPlayList(const char *listName);
	bool _clearPlayList(void);
	
public:	
	TAlsaPlayer(void){_saved = false; playerStatus.isPaused = false;}
	bool runCommand(const char *cmd,const char *arg);
	bool updateStatus(void);
	void saveState(void);
	void restoreState(void);

};

bool TAlsaPlayer::runCommand(const char *cmd,const char *arg) {
	bool res;
//	int intVals;
	if(strcmp(cmd,"load_playlist") == 0)
		res = _loadPlayList(arg);
	else if(strcmp(cmd,"clear_playlist") == 0) {
		ap_stop(_sNum);
		res = _clearPlayList();
	}	
	else if(strcmp(cmd,"play") == 0) {
		ap_unpause(_sNum);
		res = (ap_play(_sNum) == 1);	
	}
	else if(strcmp(cmd,"stop") == 0) {
		playerStatus.isPaused = false;
		ap_unpause(_sNum);
		res = (ap_stop(_sNum) == 1);
	}	
	else if(strcmp(cmd,"next") == 0) 
		res = (ap_next(_sNum) == 1);
	else if(strcmp(cmd,"prev") == 0) 
		res = (ap_prev(_sNum) == 1);
	else if(strcmp(cmd,"pause") == 0) {
		res = (ap_pause(_sNum) == 1);
		playerStatus.isPaused = true;
	}	
	else if(strcmp(cmd,"resume") == 0) {
		res = (ap_unpause(_sNum) == 1);
		playerStatus.isPaused = false;
	}	
	else if(strcmp(cmd,"jump") == 0) {
		res = (ap_set_position(_sNum,atoi(arg)) == 1);
	}	
	else if(strcmp(cmd,"track") == 0) {
		res = (ap_jump_to(_sNum,atoi(arg)) == 1);
	}
	else if(strcmp(cmd,"status") == 0) {
		res = true;
	}
	else res = false;
	updateStatus();
	return res;	
}

bool TAlsaPlayer::_loadPlayList(const char *listName){
	char *path = (char *) malloc(strlen(ALSA_PLAYLIST_PATH) + strlen(listName) +5);
	sprintf(path,"%s/%s",ALSA_PLAYLIST_PATH, listName);
	if(ap_add_playlist(_sNum,path)) {
		free(path); 
		return true;
	}
	free(path);
	return false;
}

bool TAlsaPlayer::_clearPlayList(void){
	ap_clear_playlist(_sNum);
	return true;
}


bool TAlsaPlayer::updateStatus(void){
	char **cTracks, charVal[AP_FILE_PATH_MAX+1];
	int count,intVal;
	ap_get_playlist(_sNum, &count, &cTracks);
	playerStatus.trackList.clear();
	for(int i = 0; i < count;i++)
		playerStatus.trackList.push_back(cTracks[i]);
	ap_is_playing(_sNum,&intVal);
	playerStatus.isPlaying = (intVal == 1);
	ap_get_playlist_position(_sNum,&playerStatus.curTrackNum);
	ap_get_length(_sNum, &playerStatus.curLength);
	ap_get_position(_sNum, &playerStatus.curPosition);
	ap_get_title(_sNum, charVal);
	playerStatus.trackTitle = charVal;
	ap_get_artist(_sNum, charVal);
	playerStatus.trackArtist = charVal;
	ap_get_album(_sNum, charVal);
	playerStatus.trackAlbum = charVal;
	ap_get_year(_sNum, charVal);
	playerStatus.trackYear = atoi(charVal);
	return true;
}

void TAlsaPlayer::saveState(void){
	updateStatus();
	ap_save_playlist(_sNum);
	_savedStatus.curTrackNum = playerStatus.curTrackNum;
	_savedStatus.curPosition = playerStatus.curPosition;
	_savedStatus.isPaused = playerStatus.isPaused;
	_savedStatus.isPlaying = playerStatus.isPlaying;
	_saved = true;
}

void TAlsaPlayer::restoreState(void){
	_loadPlayList("latest.m3u");
	if(_saved) {
		ap_jump_to(_sNum, _savedStatus.curTrackNum);
		if(_savedStatus.isPlaying) {
			ap_play(_sNum);
			ap_set_position(_sNum, _savedStatus.curPosition);
			if(_savedStatus.isPaused) ap_pause(_sNum);
			else ap_unpause(_sNum);
		} else {
			ap_stop(_sNum);
		}	
	}
	updateStatus();
}

// Класс TAlsaChannel
TAlsaChannel::TAlsaChannel(const char *name) : TChannel(name)
{
	_tag = "AlsaChannel";
	_typeString = "file";
	player = new TAlsaPlayer();
}

void TAlsaChannel::select(void)
{
	DBG(_tag,"select");
	adauSelectAnalogInput(0, 0);
	adauI2sOn();
	adauI2sGain(0.5);
	_start();
	player->restoreState();	
}

void TAlsaChannel::unselect(void){
	TChannel::unselect();
	player->saveState();
	_stop();
}

bool TAlsaChannel::_start(void){
	char cmd[1024];
	if(!_isRunning()) {
		sprintf(cmd, "%s --session-name %s --device %s -i daemon --quiet &",
			ALSA_PLAYER_CMD, ALSA_PLAYER_SESSION_NAME,ALSA_PLAYER_SOUND_DEVICE);
		DBG(_tag,"Run cmd: %s",cmd);
		system(cmd);
		DBG(_tag,"Command finished");
		usleep(100000L); 
		if(!_isRunning()) {
			LOGE(_tag,"Can not start Alsa player");
			return false;
		}
	}
	return true;	
}
/*
void TAlsaChannel::_initPlayList(void){
	struct dirent *pDirent;
    DIR *pDir;
	char path[255];
	int pLen;
	const char *src = "/home/artem/net/media/Audio/Collections/My";
	pDir = opendir(src);
	if(!pDir) return;
	while ((pDirent = readdir(pDir)) != NULL) {
		    if(pDirent->d_type  & DT_REG) {
				sprintf(path,"%s/%s",src,pDirent->d_name);
				ap_add_path(_sNum, path);
				ap_get_playlist_length(_sNum, &pLen);
				DBG(_tag,"Add file %s, list length %d",pDirent->d_name,pLen);
			}
            
    }
}
*/
bool TAlsaChannel::_stop(){
	if(!_isRunning()) return true;
	if(!ap_quit(_sNum)){
		LOGE(_tag,"Can not stop Alsa player (process not started)");
		return false;
	}
	_sNum = -1;
	return true;	
}

	
