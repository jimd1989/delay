#pragma once

#include <sndio.h>

typedef struct sio_hdl SioHdl;
typedef struct sio_par SioPar;

typedef struct Sndio {
  SioHdl        * handle;
  SioPar          parameters;
} Sndio;

Sndio sndio(void);
