#include "dsp.h"
#include "interpolation.h"

void setFloat(InterpolatedFloat *i, float f) {
  i->phase = 0.0f;
  i->old = i->new;
  i->new = f;
}

float getFloat(InterpolatedFloat *i) {
  float f = INTERPOLATE(i->old, i->new, i->phase);
  i->phase = TRUNC(i->phase + INTERPOLATION_INC, 1.0f);
  return f;
}

void setInt(InterpolatedInt *i, size_t n) {
  i->phase = 0.0f;
  i->old = i->new;
  i->new = n;
}

size_t getInt(InterpolatedInt *i) {
  size_t n = (size_t)INTERPOLATE(i->old, i->new, i->phase);
  i->phase = TRUNC(i->phase + INTERPOLATION_INC, 1.0f);
  return n;
}
