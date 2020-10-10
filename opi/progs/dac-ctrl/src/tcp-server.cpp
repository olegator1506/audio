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
#include <jsoncpp/json/json.h>
#include <iostream>
#include "log/log.h"
#include "commands.h"
#include "classes/selector.h"
#include "config.h"
#define TCP_BUFFER_SIZE 1024
#define SA struct sockaddr 


static const char *commands[] = {
	"ch_sel_next",
	"ch_sel_prev",
	"ch_sel_num",
	"eq",
	"adau_reload",
	"eq_reset",
	"get_state",
	NULL
};
static int sockfd;
static const char *TAG ="tcpServer";

static char **splitArg(char *args,int num){
	static char *pch[10],*p;
	p = strtok (args, " ");
	for(int i = 0; i<num;i++){
		if(p == NULL) return NULL;
		pch[i] = p;
		p = strtok (NULL, " ");		
	}
	return pch;	
}

static void _handleConnection(int fd){
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
			case CMD_ADAU_RELOAD:
				Selector->reload();	
				break;
			case CMD_EQ_RESET:
				Selector->eqReset();
				break;
			case CMD_GET_STATE:
				Json::StyledWriter styledWriter;
				Json::Value conf = Selector->getStateJson();
				std::string s = styledWriter.write(conf);
				const char *c = s.c_str(); 
				puts(c);
				break;

		}
	} 
}


bool serverRun(void) {
    int connfd; 
	socklen_t  len = 0;
    struct sockaddr_in cli; 

	while(1){
    	connfd = accept(sockfd, (SA*)&cli, &len); 
    	if (connfd < 0) { 
        	LOGE(TAG, "server acccept failed...\n"); 
        	return false;
    	} 
    	else
        	LOGI(TAG, "server acccept the client...\n"); 
  
    // Function for chatting between client and server 
    	_handleConnection(connfd); 
        close(sockfd); 
		break;
	}
}

bool initServer(void){
    struct sockaddr_in servaddr; 
  
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
  
    // Accept the data packet from client and verification 
}
 


