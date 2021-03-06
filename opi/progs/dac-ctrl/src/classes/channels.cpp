#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <jsoncpp/json/json.h>
#include "log/log.h"
#include "pcf/pcf.h"
#include "adau17x/adau17x.h"
#include "channels.h"
#include "config.h"


TChannel::TChannel(const char *name){
	_name = name;
	_selected = false;
	_typeString = "";
	player = NULL;
	dac = new DacCtrl;
	DBG(_tag,"Construct %s", name);

};
void TChannel::select(void){
	_selected = true;
	dac->apply();
}

Json::Value TChannel::getStateJson(){
	_jsonState.clear();
	_jsonState["name"]=_name;
	_jsonState["type"]=_typeString;
	_jsonState["selected"]=_selected;
	_jsonState["auxNum"]=0;
	_jsonState["track_support"]=false;
	_jsonState["player_support"]=false;
	Json::Value jval;
	_jsonState["track"] = jval;
	_jsonState["player"] = jval;	
	return _jsonState;
}

int TChannel::_checkProcessRun(const char *pidFileName){
  int pid;
	FILE *fl = fopen(pidFileName,"r");
	if(!fl) return 0;
	if(fscanf(fl,"%d",&pid) != 1) {
		fclose(fl);
		return 0;
	}
	fclose(fl);
	if(pid <= 0) return 0;
	if(kill(pid,0) == 0) // pocess with this pid exists
		return pid;
	return 0;	
}

TAuxChannel::TAuxChannel(const char *name, int inputNum) : TChannel(name)
{
	_tag = "AuxChannel";
	_auxNum = inputNum;
	_typeString = "aux";
}	

void TAuxChannel::select(void) {
	adauI2sOff();
	adauSelectAnalogInput(_auxNum,5);
//	pcfSelAnalogInput(_auxNum);
	TChannel::select();
	dac->apply();
}

// Класс TDiffChannel
TDiffChannel::TDiffChannel(const char *name) : TChannel(name)
{
	_tag = "DiffChannel";
	_typeString = "line";
}	
void TDiffChannel::select(void) {
	adauI2sOn();
	TChannel::select();

}

// Класс TSpotify
TSpotify::TSpotify(const char *name) : TChannel(name){
	_tag = "Spotify";
	_typeString = "spotify";
}

void TSpotify::select(void){
//	exec
	TChannel::select();
	DBG(_tag,"select");
	adauSelectAnalogInput(0, 0);
	adauI2sOn();
//	adauI2sGain(0.5);
	_start();
}
    
void TSpotify::unselect(void){
//	exec
	TChannel::unselect();
	_stop();
}

bool TSpotify::_start(){
	if(_checkProcessRun(SPOTIFY_PID_FILE)) // Spotify process already running
		return true;
	char cmd[1024];
/*
	sprintf(cmd, "%s --username %s --password %s --pid %s --device-name %s --device %s --on-song-change-hook %s &",
	SPOTIFY_DAEMON_CMD,SPOTIFY_USERNAME,SPOTIFY_PASSWORD,SPOTIFY_PID_FILE,SPOTIFY_DEVICE_NAME,SPOTIFY_SOUND_DEVICE,SPOTIFY_HOOK);
*/
	sprintf(cmd, "%s --username %s --password %s --pid %s --device-name %s --device %s &",
	SPOTIFY_DAEMON_CMD,SPOTIFY_USERNAME,SPOTIFY_PASSWORD,SPOTIFY_PID_FILE,SPOTIFY_DEVICE_NAME,SPOTIFY_SOUND_DEVICE);
    DBG(_tag,"Run cmd: %s",cmd);
	system(cmd);
	DBG(_tag,"Command finished");
	return true;	
}

bool TSpotify::_stop(){
	DBG(_tag,"Stop spotifyd daemon");
	int pid = _checkProcessRun(SPOTIFY_PID_FILE);
	if(!pid) {// Spotify process not running
		DBG(_tag,"Spotifyd not running");
		return true;
	}	
	kill(pid, SIGTERM);
	unlink(SPOTIFY_PID_FILE);
	DBG(_tag,"Kill Spotifyd process with PID = %d",pid);
	return true;	
}

// TMpd Channel
TMpdChannel::TMpdChannel(const char *name) : TChannel(name){
	_tag = "Mpd";
	_typeString = "mpd";
}
void TMpdChannel::select(void){
	TChannel::select();
	DBG(_tag,"select");
	adauSelectAnalogInput(0,0);
	adauI2sOn();
	_start();
}
    
void TMpdChannel::unselect(void){
//	exec
	TChannel::unselect();
	_stop();
}

bool TMpdChannel::_start(){
	if(_checkProcessRun(MPD_PID_FILE)) // Spotify process already running
		return true;
	char cmd[1024];
	sprintf(cmd, "%s",MPD_DAEMON_CMD);
    DBG(_tag,"Run cmd: %s",cmd);
	system(cmd);
	DBG(_tag,"Command finished");
	return true;	
}

bool TMpdChannel::_stop(){
	char cmd[1024];

	DBG(_tag,"Stop MPD daemon");
	int pid = _checkProcessRun(MPD_PID_FILE);
	if(!pid) {// Spotify process not running
		DBG(_tag,"MPD not running");
		return true;
	}	
	sprintf(cmd, "%s --kill",MPD_DAEMON_CMD);
    DBG(_tag,"Run cmd: %s",cmd);
	system(cmd);
	DBG(_tag,"Kill MPD process with");
	return true;	
}


