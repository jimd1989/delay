#pragma once

#include <unistd.h>

#include "../audio/audio_settings.h"
#include "filter.h"
#include "interpolation.h"
#include "parameters.h"

typedef struct Variables {
  size_t                  heapSize;
  size_t                  phaseSize;
  float                   chan;
  float                   maxDelay;
  float                   rate;
  float                 * currentSample;
  float                 * otherSample;
  InterpolatedFloat       a;
  InterpolatedFloat       b;
  InterpolatedFloat       c;
  InterpolatedFloat       feedback;
  InterpolatedFloat       pan;
  InterpolatedFloat       volume;
  InterpolatedFloat       wetness;
  Filter                  delayTime;
} Variables;

void inc(Variables *);
Variables variables(Parameters, AudioSettings, float *, float *);
