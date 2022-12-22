#pragma once

#include <stdint.h>
#include <unistd.h>

#include "../input/parameters.h"
#include "audio_settings.h"
#include "delay.h"
#include "interpolation.h"
#include "sndio.h"

typedef struct Audio {
  size_t                  bytesRead;
  InterpolatedFloat       lRecordingVol;
  InterpolatedFloat       rRecordingVol;
  Delay                   delay;
  uint8_t               * buffer;
  AudioSettings           settings;
  Sndio                   sndio;
} Audio;

Audio audio(Parameters);
void startAudio(Audio *);
void playAudio(Audio *);
void stopAudio(Audio *);
void setRecordingVol(Audio *, bool, float);
