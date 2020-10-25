#include <iostream>
#include <vector>
#include <string>

#ifndef __PLAYLIST_H__
#define __PLAYLIST_H__
class PlayList {
protected:
public:
    std::vector<std::string> listNames;
	PlayList(void);
};
#endif

extern PlayList *playList;