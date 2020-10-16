#ifndef __EQ_H__
#define __EQ_H__
#include <stdint.h>
#include "60.h"
#include "230.h"
#include "910.h"
#include "3k6.h"
#include "10k.h"
#include "14k.h"

#define EQ_LEVEL_MIN -10 
#define EQ_LEVEL_MAX  10
#define EQ_MAX_BAND_NUM 5
const uint8_t *_eqData[] = {
  eqBand60,
  eqBand230,
  eqBand910,
  eqBand3k6,
  eqBand10k,
  eqBand14k,
};
#endif