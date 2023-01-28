#include "../audio/audio_settings.h"
#include "filter.h"
#include "interpolation.h"
#include "parameters.h"
#include "variables.h"

void inc(Variables *v) {
  incFloat(&v->a);
  incFloat(&v->b);
  incFloat(&v->c);
  incFloat(&v->feedback);
  incFloat(&v->pan);
  incFloat(&v->volume);
  incFloat(&v->wetness);
  applyFilter(&v->delayTime);
}

Variables variables(Parameters p, AudioSettings a, float *x, float *y) {
  Variables v = {0};
  v.chan = a.chan;
  v.heapSize = p.heapSize;
  v.phaseSize = p.phaseSize;
  v.maxDelay = p.maxDelay;
  v.rate = a.rate;
  v.currentSample = x;
  v.otherSample = y;
  v.a = interpolatedFloat(p.interpolationFrames);
  v.b = interpolatedFloat(p.interpolationFrames);
  v.c = interpolatedFloat(p.interpolationFrames);
  v.feedback = interpolatedFloat(p.interpolationFrames);
  v.pan = interpolatedFloat(p.interpolationFrames);
  v.volume = interpolatedFloat(p.interpolationFrames);
  setInterpolatedFloat(&v.volume, 0.1f);
  v.wetness = interpolatedFloat(p.interpolationFrames);
  v.delayTime = filter(0.0f, v.rate, 0.0f, 0.0f, 1.0f);
  return v;
}
