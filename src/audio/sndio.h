#pragma once

#include <stdint.h>
#include <sndio.h>
#include <unistd.h>

typedef struct sio_hdl SioHdl;
typedef struct sio_par SioPar;

#define SNDIO_BITS (unsigned int)16
#define SNDIO_RCHAN (unsigned int)2
#define SNDIO_PCHAN (unsigned int)2
#define SNDIO_RATE (unsigned int)48000
#define SNDIO_RESOLUTION (unsigned int)375
#define SNDIO_BUF_SIZE (unsigned int)SNDIO_RATE / SNDIO_RESOLUTION

typedef struct SndioChannel {
  SioHdl        * handle;
  SioPar          parameters;
} SndioChannel;

typedef struct Sndio {
  SndioChannel  play;
  SndioChannel  rec;
} Sndio;

Sndio sndio(void);
size_t readSndio(SndioChannel *, uint8_t *, size_t);
size_t writeSndio(SndioChannel *, uint8_t *, size_t);
