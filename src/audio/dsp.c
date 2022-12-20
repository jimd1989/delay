#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>

#include "dsp.h"

int16_t fromFloat(float x) {
  float r = (rand() / ((float)RAND_MAX * 0.5f)) - 1.0f;
  r /= (float)(USHRT_MAX + 1);
  return (int16_t)roundf(CLIP(x + r) * (float)SHRT_MAX);
}
