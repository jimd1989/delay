#pragma once

#include <stdbool.h>
#include <unistd.h>

#include "../input/interpolation.h"
#include "audio_settings.h"

typedef struct DelayBuffer {
  size_t                  size;
  size_t                  writeHead;
  InterpolatedInt         delay;
  InterpolatedFloat       delayMix;
  InterpolatedFloat       feedback;
  InterpolatedFloat       pan;
  InterpolatedFloat       volume;
  InterpolatedFloat       wet;
  float                 * data;
} DelayBuffer;

typedef struct Delay {
  float         lSample;
  float         rSample;
  DelayBuffer   left;
  DelayBuffer   right;
} Delay;

void mixDelay(Delay *, float, float);
void killDelay(Delay);
void setDelayTime(Delay *, size_t, bool, float);
void setFeedback(Delay *, bool, float);
void setPan(Delay *, bool, float);
void setWetDry(Delay *, bool, float);
void setDelayVolume(Delay *, bool, float);
Delay delay(AudioSettings, float);
