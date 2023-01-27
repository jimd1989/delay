#include <err.h>
#include <sndio.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include "sndio.h"

static SndioChannel sndioChannel(unsigned int, size_t);

static SndioChannel sndioChannel(unsigned int mode, size_t rate) {
  SndioChannel s = {0};
  s.handle = sio_open(SIO_DEVANY, mode, 0);
  if (s.handle == NULL) {
    errx(-1, "couldn't open sndio handle");
  }
  sio_initpar(&s.parameters);
  s.parameters.bits = SNDIO_BITS;
  s.parameters.le = SIO_LE_NATIVE;
  s.parameters.rchan = SNDIO_RCHAN;
  s.parameters.pchan = SNDIO_PCHAN;
  s.parameters.rate = rate;
  s.parameters.appbufsz = SNDIO_BUF_SIZE(rate);
  if (!sio_setpar(s.handle, &s.parameters)) {
    errx(-1, "couldn't apply sndio settings");
  }
  if (!sio_getpar(s.handle, &s.parameters)) {
    errx(-1, "couldn't get sndio settings");
  }
  if (s.parameters.pchan != 2) {
    errx(-1, "expected stereo IO for sndio");
  }
  if (s.parameters.rchan != 2) {
    errx(-1, "expected stereo IO for sndio");
  }
  if (s.parameters.rate != rate) {
    warnx("hardware settings demand rate of %u", s.parameters.rate);
  }
  return s;
}

size_t readSndio(SndioChannel *s, uint8_t *buffer, size_t n) {
  return sio_read(s->handle, buffer, n);
}

size_t writeSndio(SndioChannel *s, uint8_t *buffer, size_t n) {
  return sio_write(s->handle, buffer, n);
}

Sndio sndio(size_t rate) {

/* Should not have to open two handles like this, but experiencing deadlock
 * when attempting full duplex with SIO_PLAY | SIO_REC. This is a temporary fix
 * from ik1-342-31132.vs.sakura.ne.jp/~uaa/gomitext/2021/202102.html */

  Sndio s = {{0}};
  s.play = sndioChannel(SIO_PLAY, rate);
  s.rec = sndioChannel(SIO_REC, rate);
  return s;
}

