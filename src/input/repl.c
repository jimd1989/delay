#include <err.h>
#include <poll.h>
#include <unistd.h>

#include "../audio/audio.h"
#include "parameters.h"
#include "parse.h"
#include "repl.h"
#include "variables.h"

static void eval(Audio *, Parsing *);
static void readLine(Audio *, Parsing);

static void eval(Audio *a, Parsing *p) {
  AudioSettings as = a->settings;
  Delay *d = &a->delay;
  switch (p->func) {
    case F_DELAY_TIME:
      setDelayTime(d, as.rate, p->right, parseFloat(p->args));
      break;
    case F_FEEDBACK:
      setFeedback(d, p->right, parseBoundFloat(p->args, 1.0f));
      break;
    case F_PAN:
      setPan(d, p->right, parseBoundFloat(p->args, 1.0f));
      break;
    case F_WET:
      setWetDry(d, p->right, parseBoundFloat(p->args, 1.0f));
      break;
    case F_VOL:
      setDelayVolume(d, p->right, parseBoundFloat(p->args, 1.0f));
      break;
    case F_RECORD_VOL:
      setRecordingVol(a, p->right, parseBoundFloat(p->args, 1.0f));
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

static void readLine(Audio *a, Parsing p) {
  size_t n = 0;
  n = read(STDIN_FILENO, p.remaining, REPL_LINE_SIZE);
  if (*p.remaining == '\n' || n < 1) {
    return;
  }
  while (!isEol(&p)) {
    parseFunc(&p);
    eval(a, &p);
  }
}

void repl(Parameters p) {
  Variables v = {0};
  Audio a = audio(p, &v);
  char line[REPL_LINE_SIZE] = {0};
  struct pollfd pfds[1] = {{0}};
  pfds[0].fd = STDIN_FILENO;
  pfds[0].events = POLLIN;
  startAudio(&a);
  warnx("Delay started; input commands. ^c exits.");
  while (poll(pfds, 1, 0) != -1) {
    if (pfds[0].revents & POLLIN) {
      readLine(&a, parsing(line));
    }
    playAudio(&a);
  }
  stopAudio(&a);
}
