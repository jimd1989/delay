#include <err.h>
#include <sndio.h>
#include <unistd.h>

#include "audio.h"
#include "audio_settings.h"
#include "sndio.h"

static AudioSettings audioSettings(SioPar);

static AudioSettings audioSettings(SioPar p) {
  size_t frames = p.appbufsz;
  AudioSettings as = {0};
  frames = frames + p.round - 1;
  frames -= frames % p.round;
  as.bits = p.bits;
  as.chan = p.rchan;
  as.rate = p.rate;
  as.bufSizeFrames = frames;
  return as;
}

Audio audio(void) {
  Audio a = {{0}};
  a.sndio = sndio();
  a.settings = audioSettings(a.sndio.parameters);
  return a;
}

void startAudio(Audio *a) {
  if (!sio_start(a->sndio.handle)) {
    errx(-1, "couldn't start sndio recording/playback");
  }
}

void stopAudio(Audio *a) {
  if (!sio_stop(a->sndio.handle)) {
    errx(-1, "couldn't stop sndio recording/playback");
  }
  sio_close(a->sndio.handle);
}
