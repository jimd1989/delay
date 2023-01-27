#include <err.h>

#include "../input/interpolation.h"
#include "interpolation.h"

void testInterpolation(void) {
  InterpolatedFloat i = interpolatedFloat(3);
  float *f = &i.product;
  i.new = 1.0f;
  i.old = 1.0f;
  warnx("interpolation");
  warnx("  freshly initialized float is fully old value");
  i.product = 1.0f;
  setInterpolatedFloat(&i, 2.0f);
  if (*f != 1.0f) {
    warnx("     ! expected 1.0f; got %f", *f);
  }
  warnx("  incrementing leans towards new");
  incFloat(&i);
  if (*f < 1.333333f) {
    warnx("     ! expected 1.333333f; got %f", *f);
  }
  warnx("  incrementing further");
  incFloat(&i);
  if (*f < 1.666666f) {
    warnx("     ! expected 1.666666f; got %f", *f);
  }
  warnx("  fully incremented");
  incFloat(&i);
  if (*f < 2.0f) {
    warnx("     ! expected 2.0f; got %f", *f);
  }
}

