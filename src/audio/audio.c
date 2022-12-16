#include <err.h>
#include <sndio.h>

#include "audio.h"
#include "sndio.h"

Audio audio(void) {
  Audio a = {{0}};
  a.sndio = sndio();
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
