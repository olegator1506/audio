#ifndef __ALSA_H__
#define __ALSA_H__
extern unsigned int _actualRate;
extern bool alsaInit(const char *name, unsigned int rate);
extern bool alsaRelease(void);
extern void alsaGenSound(void);
extern void meandr(int frequency,int amplitude);
extern void sinus(int frequency,int amplitude);
#endif // !__ALSA_H__#define __ALSA_H__
