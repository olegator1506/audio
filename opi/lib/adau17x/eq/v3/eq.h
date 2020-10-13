#ifndef __EQ_H__
#define __EQ_H__
#include <stdint.h>
#include "50.h"
#include "200.h"
#include "1k.h"
#include "4k.h"
#include "10k.h"

#define EQ_LEVEL_MIN -15 
#define EQ_LEVEL_MAX 15
#define EQ_MAX_BAND_NUM 4
const uint8_t *_eqData[] = {
  eqBand50,
  eqBand200,
  eqBand1k,
  eqBand4k,
  eqBand10k
};
#endif