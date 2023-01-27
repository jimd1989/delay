#include <err.h>
#include <sndio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#include "../input/interpolation.h"
#include "../input/variables.h"
#include "../vm/interpreter.h"
#include "../vm/vm.h"
#include "audio.h"
#include "audio_settings.h"
#include "dsp.h"
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
  as.bufSizeBytes = frames * as.chan * sizeof(int16_t);
  return as;
}

void startAudio(Audio *a) {
  if (!sio_start(a->sndio.play.handle)) {
    errx(-1, "couldn't start sndio playback");
  }
  if (!sio_start(a->sndio.rec.handle)) {
    errx(-1, "couldn't start sndio recording");
  }
}

void playAudio(Audio *a) {
  float l = 0.0f;
  float r = 0.0f;
  int16_t s = 0;
  size_t n = 0;
  size_t m = 0;
  uint8_t *byteBuffer = a->buffer;
  int16_t *sampleBuffer = (int16_t *)a->buffer;
  for (; m < a->bytesRead ; n += 2, m += 4) {
    incFloat(&a->lRecordingVol);
    incFloat(&a->rRecordingVol);
    inc(a->lVar);
    inc(a->rVar);
    *a->l = FROM_I16(sampleBuffer[n])   * a->lRecordingVol.product;
    *a->r = FROM_I16(sampleBuffer[n+1]) * a->rRecordingVol.product;
    interpret(&a->lVm.interpreter);
    interpret(&a->rVm.interpreter);
    l = a->lVm.interpreter.l + a->rVm.interpreter.l;
    r = a->lVm.interpreter.r + a->rVm.interpreter.r;
    s = fromFloat(l);
    byteBuffer[m]   = (uint8_t)(s & 255);
    byteBuffer[m+1] = (uint8_t)(s >> 8);
    s = fromFloat(r);
    byteBuffer[m+2] = (uint8_t)(s & 255);
    byteBuffer[m+3] = (uint8_t)(s >> 8);
  }
  writeSndio(&a->sndio.play, byteBuffer, a->bytesRead);
  a->bytesRead = readSndio(&a->sndio.rec, byteBuffer, a->settings.bufSizeBytes);
}

void stopAudio(Audio *a) {
  if (!sio_stop(a->sndio.play.handle)) {
    errx(-1, "couldn't stop sndio playback");
  }
  sio_close(a->sndio.play.handle);
  if (!sio_stop(a->sndio.rec.handle)) {
    errx(-1, "couldn't stop sndio recording");
  }
  sio_close(a->sndio.rec.handle);
  free(a->buffer);
  killVm(&a->lVm);
  killVm(&a->rVm);
}

Audio audio(Parameters p, Variables *vl, Variables *vr, float *l, float *r) {
  Audio a = {0};
  a.lRecordingVol = interpolatedFloat(p.interpolationFrames);
  a.rRecordingVol = interpolatedFloat(p.interpolationFrames);
  setInterpolatedFloat(&a.lRecordingVol, 1.0f);
  setInterpolatedFloat(&a.rRecordingVol, 1.0f);
  a.sndio = sndio(p.sampleRate);
  a.settings = audioSettings(a.sndio.play.parameters);
  a.buffer = calloc(a.settings.bufSizeBytes, 1);
  a.bytesRead = a.settings.bufSizeFrames * a.settings.chan * sizeof(int16_t);
  a.l = l;
  a.r = r;
  *vl = variables(p, a.settings, a.l, a.r);
  *vr = variables(p, a.settings, a.r, a.l);
  a.lVar = vl;
  a.rVar = vr;
  a.lVm = vm(a.lVar);
  a.rVm = vm(a.rVar);
  return a;
}
