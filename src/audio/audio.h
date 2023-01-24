#pragma once

#include <stdint.h>
#include <unistd.h>

#include "../input/interpolation.h"
#include "../input/parameters.h"
#include "../input/variables.h"
#include "../vm/vm.h"
#include "audio_settings.h"
#include "delay.h"
#include "sndio.h"

typedef struct Audio {
  uint8_t               * buffer;
  float                 * l;
  float                 * r;
  Variables             * lVar;
  Variables             * rVar;
  size_t                  bytesRead;
  InterpolatedFloat       lRecordingVol;
  InterpolatedFloat       rRecordingVol;
  Delay                   delay;
  AudioSettings           settings;
  Sndio                   sndio;
  Vm                      lVm;
  Vm                      rVm;
} Audio;

void startAudio(Audio *);
void playAudio(Audio *);
void stopAudio(Audio *);
void setRecordingVol(Audio *, bool, float);
Audio audio(Parameters, Variables *, Variables *, float *, float *);
