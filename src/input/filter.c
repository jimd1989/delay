#include <math.h>

#include "filter.h"

#define TWOPI (float)(2.0f * M_PI)
#define EPSILON 0.00001f

void applyFilter(Filter *f) {
  f->z = (f->target * f->b) + (f->z * f->a);
}

void setFilter(Filter *f, float x) {
  float samples = x * f->rate;
  float delta = fabsf(x - f->time);
  *f = filter(delta, f->rate, samples, f->z, f->slew);
}

Filter filter(float t, float r, float x, float z, float slew) {
  float tt = t ? t : EPSILON;
  Filter f = {0};
  f.rate = r;
  f.slew = slew;
  f.a = exp(-TWOPI / (tt * f.slew * f.rate));
  f.b = 1.0f - f.a;
  f.z = z;
  f.target = x;
  f.time = tt;
  return f;
}
