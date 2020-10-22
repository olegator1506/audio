#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <vector>
#include <string>
#include <alsaplayer/control.h>
#include "adau17x/adau17x.h"
#include "channels.h"
#include "config.h"


static int _sNum = -1;
std::vector<std::string> _playLists;
static int _isRunning(void){
	int res = ap_find_session(ALSA_PLAYER_SESSION_NAME,&_sNum);
	if(!res) 
		return false;
	return true;
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
	adauSelectAnalogInput(0, 0);
	adauI2sOn();
	adauI2sGain(0.5);
	_start();
}

void TAlsaChannel::unselect(void){
	TChannel::unselect();
	_stop();
}

bool TAlsaChannel::_start(void){
	char cmd[1024];
	int pLen;
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
//	_initPlayList();
//	ap_save_playlist(_sNum);
				ap_get_playlist_length(_sNum, &pLen);
				DBG(_tag,"Plist length %d",pLen);

	return true;	
}

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

bool TAlsaChannel::_stop(){
	if(!_isRunning()) return true;
	if(!ap_quit(_sNum)){
		LOGE(_tag,"Can not stop Alsa player (process not started)");
		return false;
	}
	return true;	
}

	
