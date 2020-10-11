#ifndef __EQ_H__
#define __EQ_H__
#include "config.h"
#include <jsoncpp/json/json.h>

class TEq {
protected:
	int _values[EQ_TOTAL_CHANNELS];
	const char *_labels[EQ_TOTAL_CHANNELS];
	Json::Value _jsonState;
	char _errorMessage[255];

public:
	TEq(void);
	void reset(void);
	bool set(int band, int value);
	Json::Value getStateJson(void);
	char *lastError(void){ return _errorMessage;}
};

extern TEq *Eq;
#endif