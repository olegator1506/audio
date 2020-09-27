#ifndef _CHANNEL_H_
#define _CHANNEL_H_
#include <esp_err.h>
#include "common.h"


extern char *channelErrorMessaage;
extern esp_err_t channelError(const char *message);
extern esp_err_t channelSelect(int);
extern esp_err_t channelSelectNext();
extern esp_err_t channelSelect(int chNum);
extern esp_err_t channelUnselect(int);
extern bool isAvailable(int chNum);
extern int channelCount(void);
extern esp_err_t channelsInit(void);
extern esp_err_t channelsEventHandler(uint8_t code,uint16_t param);
extern esp_err_t channelPlay(void);
extern int channelNextTrack(void);
extern int channelPrevTrack(void);
extern esp_err_t selectFolder(int);
extern esp_err_t channelNextFolder(void);
extern esp_err_t channelPrevFolder(void);
extern esp_err_t channelPause(void);
extern esp_err_t channelResume(void);
extern esp_err_t channelSwitchPause(void);
extern esp_err_t channelStop(void);
extern esp_err_t channelVolume(int volume);
extern esp_err_t channelEqualizer(int volume);
extern void channelBtState(bool state);
extern void channelBtSetAttr(int attrId, char *attrText);
#endif