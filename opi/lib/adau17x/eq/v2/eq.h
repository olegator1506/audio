#ifndef __EQ_H__
#define __EQ_H__
#include <stdint.h>
#include "31.h"
#include "62.h"
#include "125.h"
#include "250.h"
#include "500.h"
#include "1k.h"
#include "2k.h"
#include "4k.h"
//#include "8k.h"
#include "10k.h"
#include "16k.h"

#define EQ_LEVEL_MIN -15 
#define EQ_LEVEL_MAX 15
#define EQ_MAX_BAND_NUM 9
const uint8_t *_eqData[] = {
  eqBand31,
  eqBand62,
  eqBand125,
  eqBand250,
  eqBand500,
  eqBand1k,
  eqBand2k,
  eqBand4k,
//  eqBand8k,
    eqBand10k,
  eqBand16k
};
#endif