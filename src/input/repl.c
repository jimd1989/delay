#include <err.h>
#include <poll.h>
#include <unistd.h>

#include "../audio/audio.h"
#include "filter.h"
#include "interpolation.h"
#include "parameters.h"
#include "parse.h"
#include "repl.h"
#include "variables.h"

#define SET_BOUND_FLOAT(R, P, X, F) (void)(\
    P->right ?\
      setInterpolatedFloat(&R->rVariables.X, parseBoundFloat(P->args, F)) :\
      setInterpolatedFloat(&R->lVariables.X, parseBoundFloat(P->args, F)))

#define SET_AUDIO_FLOAT(R, P, X, F) (void)(\
    P->right ?\
      setInterpolatedFloat(&R->audio.l##X, parseBoundFloat(P->args, F)) :\
      setInterpolatedFloat(&R->audio.r##X, parseBoundFloat(P->args, F)))

static void eval(Repl *, Parsing *);
static void readLine(Repl *, Parsing);

static void eval(Repl *r, Parsing *p) {
  switch (p->func) {
    case F_DELAY_TIME:
      if (p->right) {
        setFilter(&r->rVariables.delayTime, parseFloat(p->args));
      } else {
        setFilter(&r->lVariables.delayTime, parseFloat(p->args));
      }
      break;
    case F_FEEDBACK:
      SET_BOUND_FLOAT(r, p, feedback, 1.0f); 
      break;
    case F_PAN:
      SET_BOUND_FLOAT(r, p, pan, 1.0f); 
      break;
    case F_WET:
      SET_BOUND_FLOAT(r, p, wetness, 1.0f); 
      break;
    case F_VOL:
      SET_BOUND_FLOAT(r, p, volume, 1.0f);
      break;
    case F_RECORD_VOL:
      SET_AUDIO_FLOAT(r, p, RecordingVol, 1.0f);
      break;
    case F_DELAY_FUNC:
      warnx("delay func not yet implemented");
      break;
    case F_MIX_FUNC:
      warnx("mix func not yet implemented");
      break;
    default:
      warnx("invalid input %c %s", p->func, p->args);
  }
}

static void readLine(Repl *r, Parsing p) {
  size_t n = 0;
  n = read(STDIN_FILENO, p.remaining, REPL_LINE_SIZE);
  if (*p.remaining == '\n' || n < 1) {
    return;
  }
  while (!isEol(&p)) {
    parseFunc(&p);
    eval(r, &p);
  }
}

void repl(Parameters p) {
  float ls = 0.0f;
  float rs = 0.0f;
  Repl r = {{0}};
  struct pollfd pfds[1] = {{0}};
  pfds[0].fd = STDIN_FILENO;
  pfds[0].events = POLLIN;
  r.audio = audio(p, &r.lVariables, &r.rVariables, &ls, &rs);
  startAudio(&r.audio);
  warnx("Delay started; input commands. ^c exits.");
  while (poll(pfds, 1, 0) != -1) {
    if (pfds[0].revents & POLLIN) {
      readLine(&r, parsing(r.line));
    }
    playAudio(&r.audio);
  }
  stopAudio(&r.audio);
}
