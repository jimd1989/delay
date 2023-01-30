#include <math.h>

#include "filter.h"

void applyFilter(Filter *f) {
  f->z = (f->x * f->a) + (f->z * f->b);
}

void setFilter(Filter *f, float seconds) {
  f->x = seconds * f->rate;
}

Filter filter(float rate) {
  Filter f = {0};
  f.rate = rate;
  f.a = 1.0f - exp(-1.0f / (0.05f * f.rate));
  f.b = 1.0f - f.a;
  return f;
}
