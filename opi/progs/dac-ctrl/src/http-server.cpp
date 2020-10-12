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

static const char *TAG ="httpServer";
static struct mg_mgr mgr;

/*
static void _sendResponse(struct mg_connection *connection, int code, Json::Value response) {
	Json::StyledWriter styledWriter;
	std::string s = styledWriter.write(response);
	const char *c = s.c_str(); 
	send(socket,c,strlen(c),0);
}
*/
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

static void _handleRequest(struct mg_connection *fd, int ev, void *p){
	char dst[255];
	int cmdCode;
	Json::Value data;
	if (ev != MG_EV_HTTP_REQUEST) return;
	struct http_message *pp = (struct http_message *)p;
    const struct mg_str *query = &(pp->query_string);
    if(mg_get_http_var(query,"cmd",dst,255) <= 0) {
		_sendErrorResponse(fd, 500, "Invalid request: command not specified");
		return;
	}
	
	cmdCode = CMD_INVALID;
	for(int i = 0; commands[i] !=NULL; i++) {
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
/*
			case CMD_ADAU_RELOAD:
				Selector->reload();	
				_sendSuccessResponse(fd, data);
				break;
			case CMD_EQ_RESET:
				Selector->eqReset();
				_sendSuccessResponse(fd, data);
				break;
*/
			case CMD_GET_STATE:
				Json::StyledWriter styledWriter;
				data = Selector->getStateJson();
				_sendSuccessResponse(fd, data);
				break;
	}
}


bool serverRun(void) {
  for (;;) {
    mg_mgr_poll(&mgr, 1000);
  }
  mg_mgr_free(&mgr);
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
//  s_http_server_opts.document_root = ".";  // Serve current directory
//  s_http_server_opts.enable_directory_listing = "yes";
	return true;
}
 


