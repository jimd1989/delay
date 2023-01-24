#include "../audio/audio_settings.h"
#include "interpolation.h"
#include "parameters.h"
#include "variables.h"

void inc(Variables *v) {
  incFloat(&v->a);
  incFloat(&v->b);
  incFloat(&v->c);
  incFloat(&v->feedback);
  incFloat(&v->pan);
  incFloat(&v->delayTime);
  incFloat(&v->volume);
  incFloat(&v->wetness);
}

Variables variables(Parameters p, AudioSettings a, float *x, float *y) {
  Variables v = {0};
  v.chan = a.chan;
  v.heapSize = p.heapSize;
  v.maxDelay = p.maxDelay;
  v.rate = a.rate;
  v.currentSample = x;
  v.otherSample = y;
  v.a = interpolatedFloat(p.interpolationFrames);
  v.b = interpolatedFloat(p.interpolationFrames);
  v.c = interpolatedFloat(p.interpolationFrames);
  v.feedback = interpolatedFloat(p.interpolationFrames);
  v.pan = interpolatedFloat(p.interpolationFrames);
  v.delayTime = interpolatedFloat(p.interpolationFrames);
  v.volume = interpolatedFloat(p.interpolationFrames);
  v.wetness = interpolatedFloat(p.interpolationFrames);
  return v;
}
