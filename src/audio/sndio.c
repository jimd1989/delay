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
  if (!sio_setpar(s.handle, &s.parameters)) {
    errx(-1, "couldn't apply sndio settings");
  }
  if(!sio_getpar(s.handle, &s.parameters)) {
    errx(-1, "couldn't get sndio settings");
  }
  return s;
}
