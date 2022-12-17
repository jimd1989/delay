#include <err.h>
#include <sndio.h>
#include <stdio.h>

#include "sndio.h"

Sndio sndio(void) {
  Sndio s = {0};
  s.handle = sio_open(SIO_DEVANY, SIO_PLAY | SIO_REC, 0);
  if (s.handle == NULL) {
    errx(-1, "couldn't open sndio handle");
  }
  sio_initpar(&s.parameters);
  s.parameters.bits = SNDIO_BITS;
  s.parameters.le = SIO_LE_NATIVE;
  s.parameters.rchan = SNDIO_RCHAN;
  s.parameters.pchan = SNDIO_PCHAN;
  s.parameters.rate = SNDIO_RATE;
  if (!sio_setpar(s.handle, &s.parameters)) {
    errx(-1, "couldn't apply sndio settings");
  }
  if (!sio_getpar(s.handle, &s.parameters)) {
    errx(-1, "couldn't get sndio settings");
  }
  if (s.parameters.rchan != s.parameters.pchan) {
    errx(-1, "couldn't initialize matching channels in sndio");
  }
  return s;
}
