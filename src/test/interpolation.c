#include <err.h>

#include "../input/interpolation.h"
#include "interpolation.h"

void testInterpolation(void) {
  InterpolatedFloat i = {0};
  float f = 0.0f;
  warnx("interpolation");
  warnx("  0.0f phase returns 1.0f");
  i.new = 1.0f;
  setFloat(&i, 2.0f);
  f = getFloat(&i);
  if (f != 1.0f) {
    warnx("     ! expected 1.0f; got %f", f);
  }
  warnx("  reading float increases phase and changes value on subsequent read");
  f = getFloat(&i);
  if (f <= 1.0f) {
    warnx("     ! expected greater than 1.0f; got %f", f);
  }
  warnx("  1.0f phase returns 2.0f");
  i.phase = 1.0f;
  f = getFloat(&i);
  if (f != 2.0f) {
    warnx("     ! expected 2.0f; got %f", f);
  }
  warnx("  phase can't exceed 1.0f");
  f = getFloat(&i);
  f = getFloat(&i);
  f = getFloat(&i);
  if (f != 2.0f) {
    warnx("     ! expected 2.0f; got %f", f);
  }
  warnx("  0.5f phase returns 1.5f");
  i.phase = 0.5f;
  f = getFloat(&i);
  if (f != 1.5f) {
    warnx("     ! expected 1.5f; got %f", f);
  }
}

