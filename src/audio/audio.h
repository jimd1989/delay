#pragma once

#include <stdint.h>
#include <unistd.h>

#include "../input/parameters.h"
#include "audio_settings.h"
#include "delay.h"
#include "sndio.h"

typedef struct Audio {
  size_t          bytesRead;
  float           recordingVol;
  Delay           delay;
  uint8_t       * buffer;
  AudioSettings   settings;
  Sndio           sndio;
} Audio;

Audio audio(Parameters);
void startAudio(Audio *);
void playAudio(Audio *);
void stopAudio(Audio *);
