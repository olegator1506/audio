#include <string.h>
#include <time.h>
#include "esp_err.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "common.h"
#include "pcf.h"
//#include "mp3.h"
//#include "st7735.h"
//#include "display.h"
#include "freertos/timers.h"

#define TOTAL_CHANNELS 7
// префиксы команд передаваемых на удаленный контроллер (Arduino)
#define CMD_PREFIX_CH_SEL 0 // Включение звукового канала, номер канала - младшие 3 бита
#define CMD_PREFIX_PWR 0x20

// биты управления питанием
#define PWR_BIT_LAMP 1

// время прогрева ламп, секунд
#define WARMING_TIME 10 
extern void btInit(void);
extern void btOn(void);
extern void btOff(void);

static bool _muteState = false;
static bool _ready = false;
// Режим разогрева ламп включается после включения питания, выключается через время WARMING_TIME 
bool _warmingMode = false; 

static const char *TAG="CHANNELS";
typedef enum {
    CH_TYPE_MP3,
    CH_TYPE_BLUETOOTH,
    CH_TYPE_INET_RADIO,
    CH_TYPE_AUX

} TChannelType;
typedef struct {
    TChannelType type; 
    int subchannel; // для MP3 1 - USB 2 - SDCard 4 - PC, для WiFi радио - номер станции, для остальных = 0
    bool selected;
    const char *name;//Символное имя канала
    bool available;// Доступность канала (например когда вставлен носитель или настроена станция)
    int outNum; // номер аудио выхода устройства (на выходном аналоговом коммутаторе)
    int curTrack;
    int curFolder;
    int curFolderTracks;
    int totalTracks;
    int totalFolders;
    TPlayerState playerState;

} TChannel;
char channelErrorMessaage[128];
time_t _lastFinishTime = 0;
bool _powerState = false;
esp_err_t channelSwitchPause(void);



#define MUTE_CHANNEL 5 // выход при выборе которого выключается звук
static TChannel _channels[TOTAL_CHANNELS] = {
    { // AUX #1 разъем на фронтальной панели
        .type = CH_TYPE_AUX,
        .subchannel = 0,
        .selected = false,
        .name = "AUX1",
        .available = true,
        .outNum = 1,
        .curTrack = -1,
        .curFolder = -1,
        .totalTracks = -1,
        .totalFolders = -1
    },
    { // USB
        .type = CH_TYPE_MP3,
        .subchannel = 1,
        .selected = false,
        .name = "USB Flash",
        .available = false,
        .outNum = 3,
        .curTrack = -1,
        .curFolder = -1,
        .totalTracks = -1,
        .totalFolders = -1
    },
    { // SD card
        .type = CH_TYPE_MP3,
        .subchannel = 2,
        .selected = false,
        .name = "SD Card",
        .available = false,
        .outNum = 3,
        .curTrack = -1,
        .curFolder = -1,
        .totalTracks = -1,
        .totalFolders = -1
    },
/*
    { // Bluetooth KN320
        .type = CH_TYPE_BLUETOOTH,
        .subchannel = 0,
        .selected = false,
        .name = "Bluetooth",
        .available = true,
        .outNum = 0,
        .curTrack = -1,
        .curFolder = -1,
        .totalTracks = -1,
        .totalFolders = -1
    },
*/
    { // WiFi
        .type = CH_TYPE_INET_RADIO,
        .subchannel = 0,
        .selected = false,
        .name = "Bluetooth",
        .available = false,
        .outNum = 2,
        .curTrack = -1,
        .curFolder = -1,
        .totalTracks = -1,
        .totalFolders = -1
    },
    { // AUX #2
        .type = CH_TYPE_AUX,
        .subchannel = 0,
        .selected = false,
        .name = "AUX2",
        .available = true,
        .outNum = 4,
        .curTrack = -1,
        .curFolder = -1,
        .totalTracks = -1,
        .totalFolders = -1
    },
    { // Bluetooth ESP
        .type = CH_TYPE_BLUETOOTH,
        .subchannel = 0,
        .selected = false,
        .name = "Bluetooth",
        .available = true,
        .outNum = 1,// i2s
        .curTrack = -1,
        .curFolder = -1,
        .totalTracks = -1,
        .totalFolders = -1
    }

};

static int _selectedChNum = -1;

static char 
    btTrack[21]= "                    ",
    btSinger[20]="                    ",
    btAlbum[20]= "                    "; 


static void _selectOutput(uint8_t num) {
    ESP_LOGI(TAG,"Select output # %d",num);
    pcfSelAnalogInput(num);    
}

// Выводит на дисплей информацию о текущем треке bluetooth
static void _btShowInfo(uint8_t mask){
/*
    if(!_ready) return;
    ESP_LOGI(TAG,"Bt show info mask %d",mask);
    if(_channels[_selectedChNum].type != CH_TYPE_BLUETOOTH) return;
    if(mask == 0) {
        ST7735_WriteString(2,25,"                      ",Font_7x10,ST7735_WHITE,ST7735_BLACK);
        ST7735_WriteString(2,40,"                      ",Font_7x10,ST7735_WHITE,ST7735_BLACK);
        ST7735_WriteString(2,55,"                      ",Font_7x10,ST7735_WHITE,ST7735_BLACK);
    }
    if(mask & 1) {
        ST7735_WriteString(2,25,"                      ",Font_7x10,ST7735_WHITE,ST7735_BLACK);
        ST7735_WriteString(2,25,btTrack,Font_7x10,ST7735_YELLOW,ST7735_BLACK);
    }    
    if(mask & 2) {
        ST7735_WriteString(2,40,"                      ",Font_7x10,ST7735_WHITE,ST7735_BLACK);
        ST7735_WriteString(2,40,btSinger,Font_7x10,ST7735_GREEN,ST7735_BLACK);
    }    
    if(mask & 4) {
        ST7735_WriteString(2,55,"                      ",Font_7x10,ST7735_WHITE,ST7735_BLACK);
        ST7735_WriteString(2,55,btAlbum,Font_7x10,ST7735_CYAN,ST7735_BLACK);
    }    
*/
}



static void _showChannel(int num) {
//    ST7735_FillRectangle(0,0,100,ST7735_HEIGHT-10,ST7735_BLACK);
//    ST7735_WriteString(2,2,_channels[num].name,Font_11x18,ST7735_BLACK,ST7735_CYAN);
}

static esp_err_t _stop(int chNum) {
    switch(_channels[chNum].playerState){
        case PLAYER_STATE_NOT_SUPPORT: break;
        case PLAYER_STATE_STOP: break;
        case PLAYER_STATE_PAUSE:
        case PLAYER_STATE_PLAY:
	        ESP_LOGI(TAG,"Stop");
            switch(_channels[chNum].type)  {
                case CH_TYPE_MP3:
//                    mp3Cmd(0x16,0,0,true);
                    break;
                case CH_TYPE_BLUETOOTH:
                    break;
                default: 
                    break;        
            }    
            _channels[chNum].playerState = PLAYER_STATE_STOP;
            break;
    }
    return ESP_OK;
}

static esp_err_t _select(int num){
    if(!_channels[num].available) return ESP_FAIL;
    ESP_LOGI(TAG,"Select channel %d",num);
    _channels[num].selected = true;
    _showChannel(num);
    _selectOutput(_channels[num].outNum);
    switch(_channels[num].type)  {
        case CH_TYPE_MP3:
//            mp3MediaSelect(_channels[num].subchannel); // Select media
            if(_channels[num].curTrack == -1) { //Содержимое носителя не получено
//                mp3Cmd(0x4f,0,0,false);// Запрашиваем список папок
            }
            break;
        case CH_TYPE_BLUETOOTH:
            btOn();
            _btShowInfo(7);
            break;
        default:
            break;        
    }   
    return ESP_OK;
}

static esp_err_t _unselect(int num){
    if(num != _selectedChNum) return ESP_OK;
    if(num == -1) return ESP_OK;
    ESP_LOGI(TAG,"Unselect channel %d",num);
    _stop(num);
    _channels[num].selected = false;
    if(_channels[num].type == CH_TYPE_BLUETOOTH) {
        _btShowInfo(0);
    }
        
    return ESP_OK;
}


// Переключение канала : сброс флага selected 
esp_err_t channelSelect(int num){
    if((num >= TOTAL_CHANNELS) && (num < 0)) return ESP_FAIL;
    if(num == _selectedChNum) return ESP_OK;    
    _unselect(_selectedChNum);
    if(_select(num) != ESP_OK) return ESP_FAIL; 
    _selectedChNum = num;
    return ESP_OK;
}


esp_err_t channelSelectNext(void){
    int num;
    _channels[_selectedChNum].selected = false; 
    for(num = _selectedChNum+1; num < TOTAL_CHANNELS;num++) 
        if(channelSelect(num) == ESP_OK) 
            return ESP_OK;
    for(num = 0; num<_selectedChNum; num++)
        if(channelSelect(num) == ESP_OK) 
            return ESP_OK;
    return ESP_FAIL;
}

esp_err_t channelSelectPrev(void){
    int num;
    _channels[_selectedChNum].selected = false; 
    for(num = _selectedChNum-1; num >=0 ;num--) 
        if(channelSelect(num) == ESP_OK) 
            return ESP_OK;
    for(num = TOTAL_CHANNELS-1; num >_selectedChNum; num--)
        if(channelSelect(num) == ESP_OK) 
            return ESP_OK;
    return ESP_FAIL;
}


void _setTotalFolders(uint16_t value) {
    ESP_LOGI(TAG,"Set total folders on channel %d = %u",_selectedChNum, value);
    _channels[_selectedChNum].totalFolders = value;
}

void _setTotalTracks(uint8_t subchannel, uint16_t value) {
    for(int i=0;i<TOTAL_CHANNELS;i++) {
        if((_channels[i].type == CH_TYPE_MP3) && (_channels[i].subchannel == subchannel)) {
            _channels[i].totalTracks = value;
        }
    }
}


esp_err_t selectFolder(int num){
    if(_channels[_selectedChNum].totalFolders == -1) return ESP_FAIL;// число папок на носителе не определено
//    if((num > _channels[_selectedChNum].totalFolders) || (num < 1 )) return ESP_FAIL; // Запрошен недопустимый номер папки
    _channels[_selectedChNum].curFolder = num;
    _channels[_selectedChNum].curFolderTracks = -1;
    ESP_LOGI(TAG,"Select folder # %d",num);
//    mp3Cmd(0x4e, num,0,false);
    return ESP_OK;
}

esp_err_t channelNextFolder(void){
    int num;
    if(_channels[_selectedChNum].totalFolders == -1 ) return ESP_FAIL;
    if(_channels[_selectedChNum].curFolder ==  _channels[_selectedChNum].totalFolders) num = 1;
    else num = _channels[_selectedChNum].curFolder + 1;
    return selectFolder(num); 
}

esp_err_t channelPrevFolder(void){
    int num;
    if(_channels[_selectedChNum].totalFolders == -1) return ESP_FAIL;
    if(_channels[_selectedChNum].curFolder ==  1) num = _channels[_selectedChNum].totalFolders;
    else  num = _channels[_selectedChNum].curFolder - 1;
    return selectFolder(num); 
}


esp_err_t channelPlay(void){
    ESP_LOGI(TAG,"Play");
    if(_channels[_selectedChNum].playerState == PLAYER_STATE_NOT_SUPPORT) return ESP_OK;// не поддерживается старстопный режим
    if(_channels[_selectedChNum].playerState == PLAYER_STATE_PAUSE) return channelSwitchPause();
    if(_channels[_selectedChNum].curFolder == -1) {// папка не выбрана
        selectFolder(1);// выбираем папку
        _channels[_selectedChNum].playerState = PLAYER_STATE_PLAY; // уст-м режим play чтобы после прочтения папки включить воспроизведение
        return ESP_OK;
    }    
    if(_channels[_selectedChNum].curFolderTracks == -1) { 
        ESP_LOGI(TAG,"Error playing track: folder not selected or empty");
        return ESP_FAIL;
    }    
//    mp3Cmd(0x0f,((_channels[_selectedChNum].curFolder & 0xff) << 8) + (_channels[_selectedChNum].curTrack & 0xff),0,true);
    _channels[_selectedChNum].playerState = PLAYER_STATE_PLAY;
    return ESP_OK;    
}

esp_err_t channelStop(void){
    if(_channels[_selectedChNum].playerState == PLAYER_STATE_NOT_SUPPORT) return ESP_OK;
    if(_channels[_selectedChNum].playerState == PLAYER_STATE_STOP) return ESP_OK;
    _stop(_selectedChNum);
    return ESP_OK;    
}

void _setTotalFolderTracks(uint16_t value) {
    ESP_LOGI(TAG,"Set folder track count = %d",value);
    _channels[_selectedChNum].curFolderTracks = value;
    _channels[_selectedChNum].curTrack = 1;
    if(_channels[_selectedChNum].playerState == PLAYER_STATE_PLAY) channelPlay(); 
}



/**
 * Определяет номер след. трека Пока что крутим в цикле текущую папку
 **/
// TODO Надо сделать в зависимости от режима (случайный выбор, цикл и т.п.)
int channelNextTrack(){
    if(_channels[_selectedChNum].curTrack == _channels[_selectedChNum].curFolderTracks) // если последний трек - переходим на первый
        _channels[_selectedChNum].curTrack = 1;
    else _channels[_selectedChNum].curTrack++;
    if(_channels[_selectedChNum].playerState == PLAYER_STATE_PLAY) channelPlay();
    return _channels[_selectedChNum].curTrack;
}
int channelPrevTrack(){
    if(_channels[_selectedChNum].curTrack == 1) // если первый трек - переходим на последний
        _channels[_selectedChNum].curTrack = _channels[_selectedChNum].curFolderTracks;
    else _channels[_selectedChNum].curTrack--;
    if(_channels[_selectedChNum].playerState == PLAYER_STATE_PLAY) channelPlay();
    return _channels[_selectedChNum].curTrack;
}


esp_err_t channelPause(void){
  ESP_LOGI(TAG,"Pause play");  
  if(_channels[_selectedChNum].playerState != PLAYER_STATE_PLAY) return ESP_OK; // плеер остановлен - ничего не делаем  
  _channels[_selectedChNum].playerState = PLAYER_STATE_PAUSE;
//  mp3Cmd(0x0e,0,0,true);
  return ESP_OK;
}

esp_err_t channelResume(void){
  if(_channels[_selectedChNum].playerState != PLAYER_STATE_PAUSE) return ESP_OK; // плеер остановлен - ничего не делаем  
  ESP_LOGI(TAG,"Resume play");  
  _channels[_selectedChNum].playerState = PLAYER_STATE_PLAY;
//  mp3Cmd(0x0d,0,0,true);
  return ESP_OK;
}

esp_err_t channelSwitchPause(void){
    if(_channels[_selectedChNum].playerState == PLAYER_STATE_PAUSE) return channelResume();
    if(_channels[_selectedChNum].playerState == PLAYER_STATE_PLAY) return channelPause();
    return ESP_OK;
}

esp_err_t channelVolume(int volume){
  ESP_LOGI(TAG,"Set volume %u",volume);  
  if(volume > 30) volume =30;
  if(volume < 0) volume =0;
//  mp3Cmd(0x06,volume,0,true);
  return ESP_OK;
}

esp_err_t channelEqualizer(int volume){
  ESP_LOGI(TAG,"Set equalizer %u",volume);  
  if(volume > 5) volume = 0;
  if(volume < 0) volume = 0;
//  mp3Cmd(0x07,volume,0,true);
  return ESP_OK;
}

int channelCount(void){
    return TOTAL_CHANNELS;
}
// Поиск и включение первого доступного канала
static void _selectFirst(){
    for(int i = 0; i < TOTAL_CHANNELS;i++) 
        if(channelSelect(i) == ESP_OK) break;

}

// Выключение звука, state = 0 включает звук,  1 выключает, 2 изменяет на противоположное
static void _mute(uint8_t state) {
    bool s = false;
    switch(state) {
        case 0: s = false;break;
        case 1: s = true;break;
        case 2: s = !_muteState;break;
        default: return;
    }
    if(s == _muteState) return;
    _muteState = s;
    if(_muteState) { // выключение звука
        ESP_LOGI(TAG,"Sound OFF");
//        ST7735_FillRectangle(0,15,100,ST7735_HEIGHT,ST7735_BLACK);
//        ST7735_WriteString(140,2,"X",Font_11x18,ST7735_RED,ST7735_BLACK);
        _selectOutput(MUTE_CHANNEL);         
    }
    else { // включение звука
        ESP_LOGI(TAG,"Sound ON");
//        ST7735_FillRectangle(140,0,20,ST7735_HEIGHT,ST7735_BLACK);
//        ST7735_FillRectangle(2,140,19,11,ST7735_WHITE);
//        ST7735_WriteString(140,2," ",Font_11x18,ST7735_RED,ST7735_BLACK);
        if(_selectedChNum == -1) {
            _selectFirst();
        } else {
            _selectOutput(_channels[_selectedChNum].outNum);
        }
    }
}


// вызывается по окончании прогрева ламп
void vPowerTimerCallback( TimerHandle_t pxTimer ) {
    ESP_LOGI(TAG," Warming timer handled");
    xTimerDelete(pxTimer,0);
    if(_selectedChNum == -1) { // Выбираем активным первый доступный канал
        _selectFirst();
    }
    else _select(_selectedChNum);
    _ready = true;
    _mute(0);
}



void _powerOn(void) {
    if(_powerState) return;
    ESP_LOGI(TAG,"Power ON");
//     displayOn();
     _powerState = true;
}

void _powerOff(void) {
    ESP_LOGI(TAG,"Power OFF");
    if(!_powerState) return;
     _mute(1);// при включении mute слышны щелчки
//     displayOff();
    btOff();
     _powerState = false;
     _ready = false;
}

void _powerSwitch() {
    if(_powerState) _powerOff();
    else esp_restart();
}


// вспомогательная функция - находит канал bluetooth
static int _findBluetooth(){
    for(int i=0; i< TOTAL_CHANNELS;i++)  // ищем Bluetooth канал
        if(_channels[i].type == CH_TYPE_BLUETOOTH) return i;
    return -1;
}
// Вызывается при получениии нового атрибута от источника (трек, исполнитель, альбом)
void channelBtSetAttr(int attrId, char *attrText){
    ESP_LOGI(TAG,"Bt set attr %d %s",attrId,attrText);
    char *target = NULL;
    int btCh = _findBluetooth();
    if(btCh == -1) return;

    switch(attrId) {
        case 1: target = btTrack;ESP_LOGI(TAG,"Set track: %s",attrText);break;
        case 2: target = btSinger;ESP_LOGI(TAG,"Set singer: %s",attrText);break;
        case 4: target = btAlbum;ESP_LOGI(TAG,"Set album: %s",attrText);break;
        default:break;
    }
    if(target != NULL) {
        int len = strlen(attrText);
        if(len > 20) len = 20;
        memcpy(target,attrText,len);
        target[len] = '\0';
    }
//    if(_channels[btCh].selected)      _btShowInfo();
}

// Вызывается при подключении/отключении bluetooth источника
void channelBtState(uint16_t param){
    bool state = (param == 1); 
    int btCh = _findBluetooth();
    if(btCh == -1) return; // не нашли
//    _channels[btCh].available = state;
    if(state) {// если ВТ подключен выбираем его
        channelSelect(btCh);
        _btShowInfo(0);
    }    
    else 
        channelSelectNext(); 
}



esp_err_t channelsEventHandler(uint8_t code,uint16_t param){
    time_t tt;
    switch(code) {
/*        
        case MY_EVENT_MP3_CONNECT:
            for(int i=0; i< TOTAL_CHANNELS;i++) {
                if(_channels[i].type != CH_TYPE_MP3)  continue;
                if(param & _channels[i].subchannel) { 
                    _channels[i].available = true;
                    if(avNum == -1) avNum = i;
                } else  _channels[i].available = false;       
            }
            if(avNum != -1) return channelSelect(avNum);
            if(!_channels[_selectedChNum].available) return channelSelectNext();
            break;
*/
        case MY_EVENT_MP3_DISCONNECT:
            for(int i=0; i< TOTAL_CHANNELS;i++) {
                if(_channels[i].type != CH_TYPE_MP3)  continue;
                _channels[i].available = false;
            }
            if(!_channels[_selectedChNum].available)  channelSelectNext();
            break;
        case MY_EVENT_MP3_MEDIA_PLUGIN:
            for(int i=0; i< TOTAL_CHANNELS;i++) 
                if((_channels[i].type == CH_TYPE_MP3) && (param == _channels[i].subchannel)) {
                    _channels[i].available = true;
                    if(_ready) channelSelect(i);
                }    
            break;
        case MY_EVENT_MP3_MEDIA_PLUGOUT:
            for(int i=0; i< TOTAL_CHANNELS;i++) 
                if((_channels[i].type == CH_TYPE_MP3) && (param == _channels[i].subchannel))
                    _channels[i].available = false;
            if(!_channels[_selectedChNum].available)  channelSelectNext();
            break;
        case MY_EVENT_MP3_ERROR:
            for(int i=0; i< TOTAL_CHANNELS;i++) {
                if(_channels[i].type != CH_TYPE_MP3)  continue;
                _channels[i].available = false;
            }
            if(!_channels[_selectedChNum].available)  channelSelectNext();
            break;
        case MY_EVENT_MP3_PLAY_TRACK_FINISH:
// модуль почему то выдает две команды подряд, поэтому вторую команду игнорируем        
            tt = time(NULL);
            if(tt > _lastFinishTime)  {
                _lastFinishTime = tt;
                channelNextTrack();
            }           
            break;    
        case MY_EVENT_MP3_USB_TOTAL_FILES:
            _setTotalTracks(1,param);
            break;
        case MY_EVENT_MP3_SD_TOTAL_FILES:
            _setTotalTracks(2,param);
            break;
        case  MY_EVENT_MP3_TOTAL_FOLDERS:
            _setTotalFolders(param);
            break;
        case  MY_EVENT_MP3_TOTAL_TRACKS:
            _setTotalFolderTracks(param);
            break;
        case MY_EVENT_BT_STATE:
            channelBtState(param);
            break;
        case MY_EVENT_BT_ATTR:
            if(_ready) _btShowInfo(param);
            break;
        case MY_EVENT_IR_CMD:
            switch(param){
                case 65: // SYS/BAND
                case 0xfe: // encoder cw
                    if(_ready) channelSelectNext();
                    break;
                case 0xfd: //encoder ccw
                    if(_ready) 
                        channelSelectPrev();
                    break; 
                case 0x0b: // Power
                    _powerSwitch();
                    break;           
                case 0x48: // Mute
                    if(_ready) 
                        _mute(2);
                    break;    
            }    
    }
    return ESP_OK;
}
esp_err_t channelsInit(){
    _selectOutput(MUTE_CHANNEL);    
//    displayOff();
    btInit();
    
// Устанавливаем состояния каналов MP3
/* 
    TMp3State *state = mp3GetState();
    if(state->connected) {
        for(int i =0; i< TOTAL_CHANNELS; i++) {
            if(_channels[i].type != CH_TYPE_MP3) continue;
            _channels[i].playerState = PLAYER_STATE_STOP;
            if((_channels[i].subchannel == 1) && state->usbPlugged) {
                _channels[i].available = true;
                ESP_LOGI(TAG,"USB media available");
            } 
            if((_channels[i].subchannel == 2) && state->sdPlugged) {
                _channels[i].available = true;
                ESP_LOGI(TAG,"SD media available");
            }    
        }
    }
*/
    _powerState = false;
    _powerOn();
    return ESP_OK;
}

    