#include "delay.h"

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#include "audio_settings.h"
#include "dsp.h"
#include "interpolation.h"

static DelayBuffer delayBuffer(size_t, float, float);
static float applyDelay(DelayBuffer *, float);

static DelayBuffer delayBuffer(size_t rate, float seconds, float pan) {
  DelayBuffer d = {0}; 
  d.size = (float)rate * seconds;
  d.data = calloc(d.size, sizeof(float));
  setInt(&d.delay, 1);
  setFloat(&d.pan, pan);
  setFloat(&d.feedback, 0.0f);
  setFloat(&d.volume, 0.1f);
  setFloat(&d.wet, 1.0f);
  return d;
}

Delay delay(AudioSettings as, float seconds) {
  Delay d = {0};
  d.left = delayBuffer(as.rate, seconds, 0.0f);
  d.right = delayBuffer(as.rate, seconds, 1.0f);
  return d;
}

static float applyDelay(DelayBuffer *d, float x) {
  size_t readHeadO = ((d->size - d->delay.old) + d->writeHead) % d->size;
  size_t readHeadN = ((d->size - d->delay.new) + d->writeHead) % d->size;
  float r = 0.0f;
  d->delayMix.old = d->data[readHeadO];
  d->delayMix.new = d->data[readHeadN];
  r = getFloat(&d->delayMix);
  d->data[d->writeHead] = x + (r * getFloat(&d->feedback));
  d->writeHead = (d->writeHead + 1) % d->size;
  return WET(x, r, getFloat(&d->wet)) * getFloat(&d->volume);
}

void mixDelay(Delay *d, float l, float r) {
  float lPan = getFloat(&d->left.pan);
  float rPan = getFloat(&d->right.pan);
  float lMix = 0.0f;
  float rMix = 0.0f;
  lMix = applyDelay(&d->left, l) * 0.5f;
  rMix = applyDelay(&d->right, r) * 0.5f;
  d->lSample = 0.0f;
  d->rSample = 0.0f;
  d->lSample += PAN_L(lMix, lPan);
  d->rSample += PAN_R(lMix, lPan);
  d->lSample += PAN_L(rMix, rPan);
  d->rSample += PAN_R(rMix, rPan);
}

void killDelay(Delay d) {
  free(d.left.data);
  free(d.right.data);
}

void setDelayTime(Delay *d, size_t rate, bool right, float seconds) {
  DelayBuffer *db = right ? &d->right : &d->left;
  setInt(&db->delay, (float)rate * seconds);
  db->delayMix.phase = 0.0f;
}

void setFeedback(Delay *d, bool right, float f) {
  DelayBuffer *db = right ? &d->right : &d->left;
  setFloat(&db->feedback, f);
}

void setPan(Delay *d, bool right, float f) {
  DelayBuffer *db = right ? &d->right : &d->left;
  setFloat(&db->pan, f);
}

void setWetDry(Delay *d, bool right, float f) {
  DelayBuffer *db = right ? &d->right : &d->left;
  setFloat(&db->wet, f);
}

void setDelayVolume(Delay *d, bool right, float f) {
  DelayBuffer *db = right ? &d->right : &d->left;
  setFloat(&db->volume, f);
}
