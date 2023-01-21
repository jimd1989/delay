#include <unistd.h>

#include "../audio/dsp.h"
#include "interpolation.h"

/* DEPRECATED */
void setFloat(InterpolatedFloat *i, float f) {
  i->phase = 0.0f;
  i->old = i->new;
  i->new = f;
}

/* DEPRECATED */
float getFloat(InterpolatedFloat *i) {
  float f = INTERPOLATE(i->old, i->new, i->phase);
  i->phase = TRUNC(i->phase + INTERPOLATION_INC, 1.0f);
  return f;
}

/* DEPRECATED */
void setInt(InterpolatedInt *i, size_t n) {
  i->phase = 0.0f;
  i->old = i->new;
  i->new = n;
}

/* DEPRECATED */
size_t getInt(InterpolatedInt *i) {
  size_t n = (size_t)INTERPOLATE(i->old, i->new, i->phase);
  i->phase = TRUNC(i->phase + INTERPOLATION_INC, 1.0f);
  return n;
}

void setInterpolatedFloat(NewInterpolatedFloat *i, float f) {
  i->phase = 0.0f;
  i->old = i->new;
  i->new = f;
}

void setInc(NewInterpolatedFloat *i, size_t lenFrames) {
  i->inc = 1.0f / (float)lenFrames;
}

void incFloat(NewInterpolatedFloat *i) {
  if (i->phase < 1.0f) {
    i->product = INTERPOLATE(i->old, i->new, i->phase);
    i->phase = TRUNC(i->phase + i->inc, 1.0f);
  }
}

NewInterpolatedFloat interpolatedFloat(size_t lenFrames) {
  NewInterpolatedFloat i = {0};
  setInc(&i, lenFrames);
  return i;
}
