#pragma once

#include <unistd.h>

#include "sndio.h"

typedef struct AudioSettings {
  size_t        bits;
  size_t        bufSizeFrames;
  size_t        chan;
  size_t        rate;
} AudioSettings;

typedef struct Audio {
  AudioSettings settings;
  Sndio         sndio;
  /* Input buffer */
  /* Delay buffer */
  /* Output buffer */
} Audio;

Audio audio(void);
void startAudio(Audio *);
void stopAudio(Audio *);
