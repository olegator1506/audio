#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <netdb.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <strings.h>
#include <string.h>
#include <string>
#include <unistd.h>
#include "pcf/pcf.h"
#include "adau17x/adau17x.h"
#include "log/log.h"
#include "alsaplayer/control.h"
#include "config.h"
#include "src/classes/channels.h"


#include <math.h>

//#define LOCAL_DEBUG 1

#define CMD_INVALID -1
#define CMD_CHSEL_NEXT 0
#define CMD_CHSEL_PREV 1
#define CMD_CHSEL_NUM 2
#define CMD_EQ 3

const char *commands[] = {
	"ch_sel_next",
	"ch_sel_prev",
	"ch_sel_num",
	"eq",
	NULL
};



#define SA struct sockaddr 

#pragma GCC diagnostic ignored "-Wwrite-strings"
#define SLAVE_ADDRESS 0x20
static const char *TAG = "Main";

int alsaSessionNum;

#ifdef LOCAL_DEBUG
bool setup(void) {
	DBG(TAG,"Initialization");
	pcfInit();
	adauInit(ADAU_CHIP_ADDRESS);
	Selector = new TSelector();
	return true;	
}
#else
bool setup(void) {
	DBG(TAG,"Initialization");
/*
	if(!ap_find_session(ALSA_PLAYER_SESSION_NAME,&alsaSessionNum)) {
		LOGE(TAG,"AlsaPlayer not started");
		return false;
	}
*/
	DBG(TAG,"AP session ID =%d\n", alsaSessionNum);
	if(!pcfInit()) return false;
//	if(!pcfSelAnalogInput(1)) return false;
	if(!adauInit(ADAU_CHIP_ADDRESS)) return false;
	Selector = new TSelector();
	return true;	
}
#endif

char **splitArg(char *args,int num){
	static char *pch[10],*p;
	p = strtok (args, " ");
	for(int i = 0; i<num;i++){
		if(p == NULL) return NULL;
		pch[i] = p;
		p = strtok (NULL, " ");		
	}
	return pch;	
}

void handleConnection(int fd){
	char buf[TCP_BUFFER_SIZE+1], *p,*args, *cmd, **argWords;
	int ret,cmdCode,i; 
	while((ret = read(fd, buf, TCP_BUFFER_SIZE)) > 0) {
		p = strchr(buf, '\r');
		if(!p) p = strchr(buf, '\n');
		if(p) *p = '\0';
		else buf[ret] = '\0';
		DBG(TAG, " Got packet: %s-",buf);
		p = strchr(buf,' ');
		if(p) {
			*p = '\0';
			args = p+1;
		} else args = NULL;
		cmd = buf;
		cmdCode = CMD_INVALID;
		for(i = 0; commands[i] !=NULL; i++) {
			if(strcmp(cmd,commands[i]) == 0) {
				cmdCode = i;
				break;
			}
		}
		if(cmdCode == CMD_INVALID) {
			LOGE(TAG, "Invalid command %s",cmd);
			continue;
		}
		switch(cmdCode) {
			case CMD_CHSEL_NEXT:
				Selector->selectNext();
				break;
			case CMD_CHSEL_PREV:	
				Selector->selectPrev();
				break;
			case CMD_EQ:
				argWords = splitArg(args,2);
				Selector->setEq(atoi(argWords[0]), atoi(argWords[1]));
				break;
					
		}
	} 
}

bool initServer(void){
    int sockfd, connfd; 
	socklen_t  len;
    struct sockaddr_in servaddr, cli; 
  
    // socket create and verification 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        LOGE(TAG, "socket creation failed"); 
        return false;
    } 
    else
        DBG(TAG, "Socket successfully created..\n"); 
    bzero(&servaddr, sizeof(servaddr)); 
  
    // assign IP, PORT 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port = htons(TCP_PORT); 
    int reuse = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int));

    // Binding newly created socket to given IP and verification 
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
        LOGE(TAG, "socket bind failed...\n"); 
        return false;
    } 
    else
        DBG(TAG, "Socket successfully binded..\n"); 
  
    // Now server is ready to listen and verification 
    if ((listen(sockfd, 5)) != 0) { 
        LOGE(TAG, "Listen failed...\n"); 
        return false;
    } 
    else
        DBG(TAG,"Server listening..\n"); 
    len = sizeof(cli); 
  
    // Accept the data packet from client and verification 
	while(1){
    	connfd = accept(sockfd, (SA*)&cli, &len); 
    	if (connfd < 0) { 
        	LOGE(TAG, "server acccept failed...\n"); 
        	return false;
    	} 
    	else
        	LOGI(TAG, "server acccept the client...\n"); 
  
    // Function for chatting between client and server 
    	handleConnection(connfd); 
        close(sockfd); 
		break;
	}
 }


int main(int argc, char **argv)
{

	setLogLevelGlobal(LOG_LEVEL);
	LOGI(TAG,"program started");
 	if(!setup()) {
		puts("Initialization error"); 
	}
	LOGI(TAG,"program started");
	initServer();
	LOGI(TAG,"program finished");
    return 0;

}

