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
  size_t                  bytesRead;
  InterpolatedFloat       lRecordingVol;
  InterpolatedFloat       rRecordingVol;
  Delay                   delay;
  uint8_t               * buffer;
  AudioSettings           settings;
  Sndio                   sndio;
  Vm                      vm;
} Audio;

void startAudio(Audio *);
void playAudio(Audio *);
void stopAudio(Audio *);
void setRecordingVol(Audio *, bool, float);
Audio audio(Parameters, Variables *);
