#include "delay.h"

#include <stdlib.h>
#include <unistd.h>

#include "audio_settings.h"
#include "dsp.h"

static DelayBuffer delayBuffer(size_t, float, float);
static float applyDelay(DelayBuffer *, float);

static DelayBuffer delayBuffer(size_t rate, float seconds, float pan) {
  DelayBuffer d = {0}; 
  d.size = (float)rate * seconds;
  d.data = calloc(d.size, sizeof(float));
  d.pan = pan;
  d.wet = 0.5f;
  d.delay = 12000;
  d.volume = 0.1f;
  d.feedback = 0.6f;
  return d;
}

Delay delay(AudioSettings as, float seconds) {
  Delay d = {0};
  d.left = delayBuffer(as.rate, seconds, 0.0f);
  d.right = delayBuffer(as.rate, seconds, 1.0f);
  return d;
}

static float applyDelay(DelayBuffer *d, float x) {
  float oldSample = d->data[d->phase];
  size_t target = (d->phase + d->delay) % d->size;
  x += (oldSample * d->feedback);
  d->data[target] += x;
  d->data[d->phase] = 0.0f;
  d->phase = (d->phase + 1) % d->size;
  return WET(x, oldSample, d->wet) * d->volume;
}

void mixDelay(Delay *d, float l, float r) {
  float mixL = 0.0f;
  float mixR = 0.0f;
  mixL = applyDelay(&d->left, l) * 0.5f;
  mixR = applyDelay(&d->right, r) * 0.5f;
  d->lSample = 0.0f;
  d->rSample = 0.0f;
  d->lSample += PAN_L(mixL, d->left.pan);
  d->rSample += PAN_R(mixL, d->left.pan);
  d->lSample += PAN_L(mixR, d->right.pan);
  d->rSample += PAN_R(mixR, d->right.pan);
}

void killDelay(Delay d) {
  free(d.left.data);
  free(d.right.data);
}
