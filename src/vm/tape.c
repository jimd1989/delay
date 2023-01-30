#include <stdlib.h>
#include <unistd.h>

#include "../audio/dsp.h"
#include "tape.h"

#define LERP_WRITE(T, N, R, S) T->data[(N)%T->size] += (S) * (R);\
                               T->data[((N)+1)%T->size] += (S) * (1.0f - (R));

float ReadTape(Tape *t, size_t index) {
  t->fadePhase = TRUNC(t->fadePhase + t->fadeInc, 1.0f);
  return t->data[index % t->size];
}

void writeTape(Tape *t, float index, float sample) {
  size_t n = (size_t)index;
  float r = index - n;
  float s = sample * t->fadePhase;
  LERP_WRITE(t, n, r, s);
  if (t->fadePhase < 1.0f) {
    /* negative modulo? */
    index += t->oldDelayOffset;
    n = (size_t)(index + t->oldDelayOffset);
    r = index - n;
    s = sample * (1.0f - t->fadePhase);
    LERP_WRITE(t, n, r, s);
  }
}

void setSlew(Tape *t, float fadeInc) {
  t->fadeInc = fadeInc;
}

void resetDelay(Tape *t, float oldDelaySamples, float newDelaySamples) {
  t->oldDelayOffset = oldDelaySamples - newDelaySamples;
  t->fadePhase = 0.0f;
}

void killTape(Tape *t) {
  free(t->data);
}

Tape tape(float seconds, size_t rate, float slew) {
  Tape t = {0};
  t.size = seconds * rate;
  t.data = calloc(t.size, sizeof(float));
  t.fadeInc = slew;
  return t;
}
