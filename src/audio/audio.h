#pragma once

#include <stdint.h>
#include <unistd.h>

#include "../input/interpolation.h"
#include "../input/parameters.h"
#include "../input/variables.h"
#include "../vm/vm.h"
#include "audio_settings.h"
#include "sndio.h"

/* Need AudioChannel Struct */ 

typedef struct Audio {
  uint8_t               * buffer;
  float                 * l;
  float                 * r;
  Variables             * lVar;
  Variables             * rVar;
  size_t                  bytesRead;
  InterpolatedFloat       lRecordingVol;
  InterpolatedFloat       rRecordingVol;
  AudioSettings           settings;
  Sndio                   sndio;
  Vm                      lVm;
  Vm                      rVm;
} Audio;

void startAudio(Audio *);
void playAudio(Audio *);
void stopAudio(Audio *);
Audio audio(Parameters, Variables *, Variables *, float *, float *);
