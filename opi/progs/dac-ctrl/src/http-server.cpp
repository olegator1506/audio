#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include <string>
#include <unistd.h>
#include <jsoncpp/json/json.h>
#include <iostream>
#include "log/log.h"
#include "commands.h"
#include "classes/selector.h"
#include "mongoose/mongoose.h"
#include "config.h"

static struct mg_serve_http_opts s_http_server_opts;
static const char *commands[] = {
	"ch_sel_next",
	"ch_sel_prev",
	"ch_sel_num",
	"eq",
	"adau_reload",
	"eq_reset",
	"get_state",
	"pub",
	"pub_spotify_stop",
	"pub_spotify_start",
	"pub_spotify_change",
	"bass",
	"player",
	NULL
};

static const char *TAG ="httpServer";
static struct mg_mgr mgr;
static sig_atomic_t s_signal_received = 0;
//static struct mg_connection *_wsConnection = NULL;

static void signal_handler(int sig_num) {
  signal(sig_num, signal_handler);  // Reinstantiate signal handler
  s_signal_received = sig_num;
}


static void _sendErrorResponse(struct mg_connection *connection, int code, const char *format,...){
	char msg[257];

	va_list list; 
	va_start(list,format);
	vsnprintf(msg, 255, format, list);
	va_end(list);
	mg_http_send_error(connection, code, msg);
}

static void _sendSuccessResponse(struct mg_connection *connection, Json::Value data){
	Json::Value response;
	response["result"] = "OK";
	response["data"] = data;
	Json::StyledWriter styledWriter;
	std::string s = styledWriter.write(response);
	const char *c = s.c_str(); 
	mg_send_head(connection, 200, strlen(c),"Access-Control-Allow-Origin: *\r\nContent-type: application/json");
	mg_send(connection, c, strlen(c));
}


static void _broadcast(struct mg_connection *nc, const char *query) {
  struct mg_connection *c;
  for (c = mg_next(nc->mgr, NULL); c != NULL; c = mg_next(nc->mgr, c)) {
    if (c == nc) continue; // Don't send to the sender. 
    mg_send_websocket_frame(c, WEBSOCKET_OP_TEXT, query, strlen(query));
  }
}

/*
static void _publish(struct mg_connection *nc, const struct mg_str *query){
	char *msg = (char*)malloc(query->len +1);
	memcpy(msg,query->p,query->len);
	msg[query->len] = '\0';
	_broadcast(nc,msg);
	free(msg);
}
*/

static void _publish(struct mg_connection *nc, const struct mg_str *query, const char *params[]){
	char param[501];
//	if(!_wsConnection) return;
	Json::Value data;
	for(int i=0;params[i];i++) {
		if(mg_get_http_var(query,params[i],param,500) <= 0) {
			_sendErrorResponse(nc, 500, "Invalid request: one or more params not specified");
			return;
		}
		data[params[i]] = param;
	}
	Json::FastWriter Wr;
	std::string s = Wr.write(data);
	const char *c = s.c_str(); 
	_broadcast(nc,c);
//	mg_send_websocket_frame(_wsConnection, WEBSOCKET_OP_TEXT, c, strlen(c));
}
static void _sendPlayerStatus(struct mg_connection *fd,Player *player){
	Json::Value data,tracksJson;
	int i,trackCount;
//	player->updateStatus();
	tracksJson.clear();
	trackCount = playerStatus.trackList.size();
	for(i=0;i<trackCount;i++){
		tracksJson.append(playerStatus.trackList[i]);
	}
	data["tracks"] = tracksJson;
	data["is_playing"] = playerStatus.isPlaying;
	data["is_paused"] = playerStatus.isPaused;
	data["track_num"] = playerStatus.curTrackNum;
	data["track_length"] = playerStatus.curLength;
	data["track_posifion"] = playerStatus.curPosition;
	data["track_title"] = playerStatus.trackTitle;
	data["track_artist"] = playerStatus.trackArtist;
	data["track_album"] = playerStatus.trackAlbum;
	data["track_year"] = playerStatus.trackYear;
	_sendSuccessResponse(fd,data);
}

static void _execPlayerCmd(struct mg_connection *fd, const struct mg_str *query){
	char dst[1024], op[255], *arg;
	Player *player = Selector->player();
	if(!player) {
		_sendErrorResponse(fd, 500, "Invalid request: player not supported");
	}
	if(mg_get_http_var(query,"op",op,255) <= 0) {
		_sendErrorResponse(fd, 500, "Invalid request: player operation not specified");
		return;
	}
	arg = (mg_get_http_var(query,"arg",dst,255) > 0) ? dst : NULL;
	if(!player->runCommand(op,arg)) {
		_sendErrorResponse(fd, 500, "Error loading play list");
		return;
	}
	_sendPlayerStatus(fd,player);
}

static void _handleHttpRequest(struct mg_connection *fd, struct http_message *pp){
	char dst[256];
	int cmdCode, i;
	static char *tmpStr;
	Json::Value data,tracksJson;
	Json::StyledWriter styledWriter;
    const struct mg_str *query = &(pp->query_string);
	tmpStr = (char*)malloc(query->len +1);
	memcpy(tmpStr,query->p,query->len);
	tmpStr[query->len] = '\n';
	DBG(TAG,"HTTP Request %s",tmpStr);
	free(tmpStr);
	const char *params[] = {"cmd","track_id","album","artist","track_name","image","duration_string","duration",NULL};
	if(!query->len) {
		mg_serve_http(fd, pp, s_http_server_opts);
		return;
	}
    if(mg_get_http_var(query,"cmd",dst,255) <= 0) {
		_sendErrorResponse(fd, 500, "Invalid request: command not specified");
		return;
	}
	
	cmdCode = CMD_INVALID;
	for(i = 0; commands[i] !=NULL; i++) {
		if(strcmp(dst,commands[i]) == 0) {
			cmdCode = i;
			break;
		}
	}
	if(cmdCode == CMD_INVALID) {
		_sendErrorResponse(fd, 500, "Invalid command %s",dst);
		return;
	}
	data.clear();
	switch(cmdCode) {
		case CMD_CHSEL_NEXT:
			Selector->selectNext();
			_sendSuccessResponse(fd, Selector->getStateJson());
			break;
		case CMD_CHSEL_PREV:	
			Selector->selectPrev();
			_sendSuccessResponse(fd, Selector->getStateJson());
			break;
		case CMD_CHSEL_NUM:
			if(mg_get_http_var(query,"num",dst,255) <= 0) {
				_sendErrorResponse(fd, 500, "Invalid request:channel number not specified");
				return;
			}
			if(Selector->select(atoi(dst)))
				_sendSuccessResponse(fd, Selector->getStateJson());
			else 
				_sendErrorResponse(fd, 500, Selector->lastError());	
			break;
			case CMD_BASS:
				if(mg_get_http_var(query,"state",dst,255) <= 0) {
					_sendErrorResponse(fd, 500, "Invalid request: bass state not specified");
					return;
				}
				Selector->superBass((strcmp(dst,"on") == 0));
				_sendSuccessResponse(fd, data);
				break;

			case CMD_EQ:
				int bandNum,val;
				if(mg_get_http_var(query,"band",dst,255) <= 0) {
					_sendErrorResponse(fd, 500, "Invalid request: band number not specified");
					return;
				}
				bandNum = atoi(dst);
				if(mg_get_http_var(query,"value",dst,255) <= 0) {
					_sendErrorResponse(fd, 500, "Invalid request: EQ value not specified");
					return;
				}
				val = atoi(dst);
				if(!Selector->setEq(bandNum,val)) {
					_sendErrorResponse(fd, 500, Selector->lastError());
					return;
				}
				_sendSuccessResponse(fd, Selector->getStateJson());
				break;


			case CMD_ADAU_RELOAD:
				Selector->reload();	
				_sendSuccessResponse(fd, data);
				break;
			case CMD_EQ_RESET:
				Selector->eqReset();
				_sendSuccessResponse(fd, data);
				break;

			case CMD_GET_STATE:
				data = Selector->getStateJson();
				_sendSuccessResponse(fd, data);
				break;
			case CMD_PUB:
			case CMD_PUB_SPOTIFY_CHANGE:
			case CMD_PUB_SPOTIFY_STOP:
			case CMD_PUB_SPOTIFY_START:
				_publish(fd,query,params);
				_sendSuccessResponse(fd, data);
				break;
			case CMD_PLAYER:
				_execPlayerCmd(fd,query);
				break;
		}

}

static void _handleRequest(struct mg_connection *fd, int ev, void *p){
	switch(ev) {
		case MG_EV_HTTP_REQUEST:
			_handleHttpRequest(fd, (struct http_message *)p);
			return;
		case MG_EV_WEBSOCKET_HANDSHAKE_DONE:
			DBG(TAG,"Ws connection established");
//			_wsConnection = fd;
			return;	
		case MG_EV_WEBSOCKET_FRAME:	
			DBG(TAG,"Ws got new frame");
			return;	
//		case MG_EV_CLOSE:
//			_wsConnection = NULL;	
	}
}


bool serverRun(void) {
  while (s_signal_received == 0)
  {
    mg_mgr_poll(&mgr, 1000);
  }
  mg_mgr_free(&mgr);
  
  return true;    
}

bool initServer(void){
	struct mg_connection *nc;
    const char *s_http_port = HTTP_SERVER_PORT;

  mg_mgr_init(&mgr, NULL);
  DBG(TAG,"Starting web server on port %s\n", s_http_port);
  nc = mg_bind(&mgr, s_http_port, _handleRequest);
  if (nc == NULL) {
    LOGE(TAG,"Failed to create listener\n");
    return false;
  }

  // Set up HTTP server parameters
  mg_set_protocol_http_websocket(nc);
  s_http_server_opts.document_root = HTTP_SERVER_ROOT_PATH;  // Serve current directory
  s_http_server_opts.enable_directory_listing = "yes";
  signal(SIGTERM, signal_handler);
  signal(SIGINT, signal_handler);
  setvbuf(stdout, NULL, _IOLBF, 0);
  setvbuf(stderr, NULL, _IOLBF, 0);

	return true;
}
 


