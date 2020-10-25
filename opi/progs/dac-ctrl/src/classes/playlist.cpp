#include <unistd.h>
#include <dirent.h>
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

PlayList *playList;