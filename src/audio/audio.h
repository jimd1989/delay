#pragma once

#include <unistd.h>

#include "../input/parameters.h"
#include "audio_settings.h"
#include "delay.h"
#include "sndio.h"

typedef struct Audio {
  AudioSettings settings;
  Delay         delay;
  Sndio         sndio;
  /* Input buffer */
} Audio;

Audio audio(Parameters);
void startAudio(Audio *);
void stopAudio(Audio *);
