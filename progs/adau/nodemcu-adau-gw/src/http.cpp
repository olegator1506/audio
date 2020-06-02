#include <ESP8266WebServer.h>
#include "debug.h"
#include "adau17x.h"

static ESP8266WebServer _server(80);

static void _httpHandle(void){
    const String action = _server.arg("action");
    DBG("HTTP handle action %s",action.c_str());
    if(action == "dspoff") adauDspOff();
    else if(action == "dspon") adauDspOn();
//    else if(action == "reload") adauDspReload();
    else if(action == "reload") adauInit();
    else if(action == "hpvol") adauOutVol(atoi(_server.arg("level").c_str()),false);
    else if(action == "linevol") adauOutVol(atoi(_server.arg("level").c_str()),true);
    else if(action == "eqlevel") adauEqSet(atoi(_server.arg("band").c_str()),atoi(_server.arg("level").c_str()));
    _server.send(200, "text/html" , "Ok" ); 
}

void httpHandle(void){
    _server.handleClient();
}
void httpInit(void) {
    _server.on("/",_httpHandle); // Ответ сервера на запрос главной страницы
    _server.begin(); //Запуск сервера
}