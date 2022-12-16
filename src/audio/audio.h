#pragma once

#include "sndio.h"

typedef struct Audio {
  Sndio sndio;
} Audio;

Audio audio(void);
void startAudio(Audio *);
void stopAudio(Audio *);
