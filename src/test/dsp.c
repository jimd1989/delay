#include <err.h>

#include "../audio/dsp.h"
#include "dsp.h"

void testDsp(void) {
  float n = 0.0f;
  float w = 0.0f;
  float d = 0.0f;
  warnx("dsp");
  warnx("  clipping ignores 0.99f");
  n = 0.99f;
  if (CLIP(0.99f) != n) {
    warnx("     ! expected 0.99f; got %f", CLIP(0.99f));
  }
  warnx("  clipping ignores -0.99f");
  n = -0.99f;
  if (CLIP(-0.99f) != n) {
    warnx("     ! expected -0.99f; got %f", CLIP(-0.99f));
  }
  warnx("  clipping chops 1.01f");
  n = 1.0f;
  if (CLIP(1.01f) != n) {
    warnx("     ! expected 1.0f; got %f", CLIP(1.01f));
  }
  warnx("  clipping chops -1.01f");
  n = -1.0f;
  if (CLIP(-1.01f) != n) {
    warnx("     ! expected -1.0f; got %f", CLIP(-1.01f));
  }
  warnx("  0.0 wetness preserves full dry signal");
  w = -1.0f;
  d = 1.0f;
  n = WET(d, w, 0.0f);
  if (n != 1.0f) {
    warnx("     ! expected 1.0f; got %f", n);
  }
  warnx("  1.0 wetness preserves full wet signal");
  w = -1.0f;
  d = 1.0f;
  n = WET(d, w, 1.0f);
  if (n != -1.0f) {
    warnx("     ! expected -1.0f; got %f", n);
  }
  warnx("  0.5 wetness mixes wet and dry signals evenly");
  w = -1.0f;
  d = 1.0f;
  n = WET(d, w, 0.5f);
  if (n != 0.0f) {
    warnx("     ! expected 0.0f; got %f", n);
  }
  warnx("  0.0 pans fully to left");
  n = PAN_L(1.0f, 0.0f);
  if (n != 1.0f) {
    warnx("     ! expected left 1.0f; got %f", n);
  }
  n = PAN_R(1.0f, 0.0f);
  if (n != 0.0f) {
    warnx("     ! expected right 0.0f; got %f", n);
  }
  warnx("  1.0 pans fully to right");
  n = PAN_L(1.0f, 1.0f);
  if (n != 0.0f) {
    warnx("     ! expected left 0.0f; got %f", n);
  }
  n = PAN_R(1.0f, 1.0f);
  if (n != 1.0f) {
    warnx("     ! expected right 1.0f; got %f", n);
  }
  warnx("  0.5 panning provides full signal in both channels");
  n = PAN_L(1.0f, 0.5f);
  if (n != 1.0f) {
    warnx("     ! expected left 1.0f; got %f", n);
  }
  n = PAN_R(1.0f, 0.5f);
  if (n != 1.0f) {
    warnx("     ! expected right 1.0f; got %f", n);
  }
  warnx("  32767 amplitude becomes ~1.0f");
  n = FROM_I16(32767);
  if (n < 0.999969f) {
    warnx("     ! expected ~1.0f; got %f", n);
  }
  warnx("  -32768 amplitude becomes -1.0f");
  n = FROM_I16(-32768);
  if (n != -1.0f) {
    warnx("     ! expected -1.0f; got %f", n);
  }
  warnx("  0 amplitude becomes 0.0f");
  n = FROM_I16(0);
  if (n != 0.0f) {
    warnx("     ! expected 0.0f; got %f", n);
  }
  warnx("  scalar 2.5f truncated to 2.0f");
  n = TRUNC(2.5f, 2.0f);
  if (n != 2.0f) {
    warnx("     ! expected 2.0f; got %f", n);
  }
  warnx("  1.0f +  1.5f truncated to 2.0f");
  n = TRUNC(1.0f + 1.5f, 2.0f);
  if (n != 2.0f) {
    warnx("     ! expected 2.0f; got %f", n);
  }
}
