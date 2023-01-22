#include <err.h>
#include <sndio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#include "../input/variables.h"
#include "../vm/vm.h"
#include "audio.h"
#include "audio_settings.h"
#include "delay.h"
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
  int16_t s = 0;
  size_t n = 0;
  size_t m = 0;
  uint8_t *byteBuffer = a->buffer;
  int16_t *sampleBuffer = (int16_t *)a->buffer;
  for (; m < a->bytesRead ; n += 2, m += 4) {
    a->l = FROM_I16(sampleBuffer[n])   * getFloat(&a->lRecordingVol);
    a->r = FROM_I16(sampleBuffer[n+1]) * getFloat(&a->rRecordingVol);
    mixDelay(&a->delay, a->l, a->r);
    s = fromFloat(a->delay.lSample);
    byteBuffer[m]   = (uint8_t)(s & 255);
    byteBuffer[m+1] = (uint8_t)(s >> 8);
    s = fromFloat(a->delay.rSample);
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
  killDelay(a->delay);
  free(a->buffer);
}

void setRecordingVol(Audio *a, bool right, float f) {
  if (right) {
    setFloat(&a->rRecordingVol, f);
  } else {
    setFloat(&a->lRecordingVol, f);
  }
}

Audio audio(Parameters p, Variables *vl, Variables *vr) {
  Audio a = {0};
  setFloat(&a.lRecordingVol, 1.0f);
  setFloat(&a.rRecordingVol, 1.0f);
  a.sndio = sndio();
  a.settings = audioSettings(a.sndio.play.parameters);
  a.buffer = calloc(a.settings.bufSizeBytes, 1);
  a.delay = delay(a.settings, p.maxDelay);
  a.bytesRead = a.settings.bufSizeFrames * a.settings.chan * sizeof(int16_t);
  *vl = variables(p, a.settings, &a.l, &a.r);
  *vr = variables(p, a.settings, &a.r, &a.l);
  a.vmL = vm(vl);
  a.vmR = vm(vr);
  return a;
}
