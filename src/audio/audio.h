#pragma once

#include <unistd.h>

#include "audio_settings.h"
#include "sndio.h"

typedef struct Audio {
  AudioSettings settings;
  Sndio         sndio;
  /* Input buffer */
  /* Delay buffer */
} Audio;

Audio audio(void);
void startAudio(Audio *);
void stopAudio(Audio *);
