#include <iostream>
#include <vector>
#include <string>

#ifndef __PLAYLIST_H__
#define __PLAYLIST_H__
class PlayList {
protected:
    Json::Value _jsonData;
    Json::Value __jsonError;
//    Json::Value _returnError(char *message);

public:
    std::vector<std::string> listNames;
	PlayList(void);
//    Json::Value loadPlayList(const char *listname);
};
#endif

extern PlayList *playList;