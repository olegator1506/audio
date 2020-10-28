#include <unistd.h>
#include <dirent.h>
#include <stdint.h>
#include <string.h>
#include <jsoncpp/json/json.h>
#include "playlist.h"
#include "config.h"


PlayList::PlayList(void) {
    struct dirent *pDirent;
    DIR *pDir;
	const char *src = ALSA_PLAYLIST_PATH;
	pDir = opendir(src);
	if(!pDir) return;
	while ((pDirent = readdir(pDir)) != NULL) {
		    if(pDirent->d_type  & DT_REG) {
                listNames.push_back(pDirent->d_name);
			}
            
    }
}
/*
Json::Value _returnError(char *message){
	__jsonError.clear();
	__jsonError["result"] = "error";
	__jsonError["message"] = message;
	return __jsonError;
}

Json::Value PlayList::loadPlayList(const char *listName){
	int len = strlen(ALSA_PLAYLIST_PATH) + strlen(listName) + 5;
	char *path = (char *) malloc(len);
	char *line  = (char *) malloc(1024);
	_jsonData.clear();
	
	snprintf(path,len-1,"%s/%s",ALSA_PLAYLIST_PATH, listNames);
	FILE *fl = fopen(path,"r");
	if(!fl) {
		_jsonData["result"] = "error";
		_jsonData["message"] = "Error opening play list file"
		free(path);free(line);
		return _jsonData;
	}
	while(!feof(fl)){
		if(fgets(line,1023,fl) {
			_jsonData["result"] = "error";
			_jsonData["message"] = "Error reading play list file";
			fclose(fl);
			free(path);free(line);
			return _jsonData;
		}

	}
} 
*/

/*
Json::Value PlayList::loadPlayList(const char *listName){
	int len = strlen(ALSA_PLAYLIST_PATH) + strlen(listName) + 5;
	char *path = (char *) malloc(len);
	char *line  = (char *) malloc(1024);
	_jsonData.clear();
	
	snprintf(path,len-1,"%s/%s",ALSA_PLAYLIST_PATH, listNames);
	FILE *fl = fopen(path,"r");
	if(!fl) {
		_jsonData["result"] = "error";
		_jsonData["message"] = "Error opening play list file"
		free(path);free(line);
		return _jsonData;
	}
	while(!feof(fl)){
		if(fgets(line,1023,fl) {
			_jsonData["result"] = "error";
			_jsonData["message"] = "Error reading play list file";
			fclose(fl);
			free(path);free(line);
			return _jsonData;
		}

	}
} 
*/
PlayList *playList;