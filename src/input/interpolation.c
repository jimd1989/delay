#include <unistd.h>

#include "../audio/dsp.h"
#include "interpolation.h"

void setInterpolatedFloat(InterpolatedFloat *i, float f) {
  i->phase = 0.0f;
  i->old = i->new;
  i->new = f;
}

void setInc(InterpolatedFloat *i, size_t lenFrames) {
  i->inc = 1.0f / (float)lenFrames;
}

void incFloat(InterpolatedFloat *i) {
  i->phase = TRUNC(i->phase + i->inc, 1.0f);
  i->product = INTERPOLATE(i->old, i->new, i->phase);
}

InterpolatedFloat interpolatedFloat(size_t lenFrames) {
  InterpolatedFloat i = {0};
  setInc(&i, lenFrames);
  return i;
}
