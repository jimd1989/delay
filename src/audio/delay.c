#include "delay.h"

#include <stdlib.h>
#include <unistd.h>

#include "audio_settings.h"

static DelayBuffer delayBuffer(size_t, float);

static DelayBuffer delayBuffer(size_t rate, float seconds) {
  DelayBuffer d = {0}; 
  d.size = (float)rate / seconds;
  d.data = calloc(d.size, sizeof(float));
  return d;
}

Delay delay(AudioSettings as, float seconds) {
  Delay d = {0};
  d.left = delayBuffer(as.rate, seconds);
  d.right = delayBuffer(as.rate, seconds);
  d.output = calloc(as.bufSizeFrames * as.chan, sizeof(float));
  return d;
}
