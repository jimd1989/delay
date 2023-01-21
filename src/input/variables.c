#include "../audio/audio_settings.h"
#include "interpolation.h"
#include "parameters.h"
#include "variables.h"

Variables variables(Parameters p, AudioSettings a) {
  Variables v = {0};
  v.chan = a.chan;
  v.heapSize = p.heapSize;
  v.maxDelay = p.maxDelay;
  v.rate = a.rate;
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
