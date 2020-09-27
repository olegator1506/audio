#ifndef _MP3_H_
#define _MP3_H_

typedef struct {
    bool connected, sdPlugged,usbPlugged,pcPlugged,playing;
    int totalFolders[2], totalFiles[2], curFolder[2],curFile[2];
    uint8_t errCode;
} TMp3State;

extern esp_err_t mp3Init(int txPin, int rxPin);
extern TMp3State* mp3GetState(void);
extern void mp3Play(uint8_t trackNum);
extern void mp3Cmd(uint8_t code, uint16_t param, uint16_t delay,bool feedback);
extern void mp3MediaSelect(uint8_t mediaNum);
#endif