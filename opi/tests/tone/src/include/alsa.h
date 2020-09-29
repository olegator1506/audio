#ifndef __ALSA_H__
#define __ALSA_H__
extern bool alsaInit(const char *name, unsigned int rate);
extern bool alsaRelease(void);
extern void alsaGenSound(int duration);
#endif // !__ALSA_H__#define __ALSA_H__
