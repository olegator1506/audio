#ifndef __EQ_H__
#define __EQ_H__
#include "config.h"
class TEq {
protected:
	int _values[EQ_TOTAL_CHANNELS];
	const char *_labels[EQ_TOTAL_CHANNELS];
public:
	TEq(void);
	void reset(void);
	void set(int band, int value);
};

extern TEq *Eq;
#endif