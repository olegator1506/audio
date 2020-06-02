#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include "config.h"
#include "debug.h"
#include "adau17x.h"
#include "led.h"
#include "http.h"

#define COMMAND_READ 0x0a
#define COMMAND_WRITE 0x0b
#define HEADER_SIZE 8


const char* ssid = "SweetHome";
const char* password = "DoYr1941?";
uint8_t pin = D7; // Это пин 13

bool _clientConnected = false;

WiFiServer server(8086);
WiFiClient client;

void setup() {

#ifdef _DEBUG_
  debugMode = true;
#endif  
  ledInit();
  Serial.begin(115200);
  delay(10);
  DBG("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    DBG("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
#ifdef USE_OTA
  // Port defaults to 8266 
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
   ArduinoOTA.setHostname("node-01");

  // No authentication by default
  // ArduinoOTA.setPassword("admin");

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_SPIFFS
      type = "filesystem";
    }

    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
#endif

  DBG("Wifi ready IP address:%s",WiFi.localIP().toString().c_str());
  pinMode(pin,INPUT);
  server.begin();
  httpInit();
//  delay(1000);
  adauInit();
  ledBlink(100);

}


void execRead(int address, int length) {
  uint8_t *buf;
  ledBlink(200);
  DBG("R: %d bytes at address %04X :",length,address);
  Serial.print('R');
  buf = (uint8_t *)malloc(length+4);
  buf[0] = COMMAND_WRITE;
  buf[1] = (0x4 + length) >> 8;
  buf[2] = (0x4 + length) & 0xff;
  buf[3] = adauRead(address, buf + 4,  length); // код возврата
  client.write(buf, 4 + length);
  free(buf);
}


void execWrite(int address, uint8_t *buf, int length) {
  ledBlink(200);
//  DBG("W: %d bytes at address %04X : %s",length,address,dbgDataStr(buf,length));
    adauWrite(address, buf, length);
//  for(int i=0;i<length;i++)         Serial.printf("%02X ",buf[i]);
}

void handleClient(void){
   uint8_t *buf;
   uint8_t header[8],command;
   unsigned int addr, len, bytesReceived;
  if(_clientConnected && !client.connected()) {
      Serial.println("Client disconnect");
      _clientConnected = false;
      return;
  } 
  if(!_clientConnected && !client.connected()) {
       client = server.available();
       return;
  }
  if(!_clientConnected && client.connected()) {
      _clientConnected = true;
      Serial.println("Client connect");
       return;
  }
  if(!_clientConnected) return;
  bytesReceived  = client.available();
  if (bytesReceived < HEADER_SIZE) return;   
  client.peekBytes(header,HEADER_SIZE);
	command = header[0];
//	total_len = (header[1] << 8) | header[2];
	len = (header[4] << 8) | header[5];
	addr = (header[6] << 8) | header[7];
  if(command == COMMAND_READ) { // чтение из ADAU
    client.read(header,HEADER_SIZE);
    execRead(addr,len);
    return;
  }  
  if(bytesReceived < (len+8)) return;
  buf = (uint8_t *)malloc(len);
  client.read(header,HEADER_SIZE);
  client.read(buf,len);
  execWrite(addr,buf,len);
  free(buf);
}

void readLevel(void){
  float left,right;
  if(!adauReadLevel(&left,&right)) return;
  Serial.printf("L: %10.7f R: %10.7f\n", left,right);  
}

void loop() {
static unsigned int last =0L;
#ifdef USE_OTA
  ArduinoOTA.handle();
#endif
/*
  Serial.println(state);
  led(state);
  state = !state;
  delay(2000);
*/
  handleClient();
  httpHandle();
  unsigned curT = millis() / 1000;
  if(curT >= (last+5)){ // Keep alive
    last = curT;
    Serial.print('.');
  }
  ledLoop();
  if((millis() % 5000) == 0) {
//    adauInit();
    ledBlink(100);
    readLevel();
  }  
}
