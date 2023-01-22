#pragma once

#include <unistd.h>

#include "../audio/audio_settings.h"
#include "interpolation.h"
#include "parameters.h"

typedef struct Variables {
  size_t                  heapSize;
  float                   chan;
  float                   maxDelay;
  float                   rate;
  float                 * currentSample;
  float                 * otherSample;
  NewInterpolatedFloat    a;
  NewInterpolatedFloat    b;
  NewInterpolatedFloat    c;
  NewInterpolatedFloat    feedback;
  NewInterpolatedFloat    pan;
  NewInterpolatedFloat    delayTime;
  NewInterpolatedFloat    volume;
  NewInterpolatedFloat    wetness;
} Variables;

Variables variables(Parameters, AudioSettings, float *, float *);
