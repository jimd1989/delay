#include <err.h>
#include <poll.h>
#include <unistd.h>

#include "../audio/audio.h"
#include "parameters.h"
#include "repl.h"

static void readLine(char *);

static void readLine(char *s) {
  size_t n = 0;
  n = read(STDIN_FILENO, s, REPL_LINE_SIZE);
  if (*s == '\n' || n < 1) {
    return;
  }
  warnx("Input received.");
}

void repl(Parameters p) {
  Audio a = audio(p);
  char line[REPL_LINE_SIZE] = {0};
  struct pollfd pfds[1] = {{0}};
  pfds[0].fd = STDIN_FILENO;
  pfds[0].events = POLLIN;
  startAudio(&a);
  warnx("Delay started; input commands. ^c exits.");
  while (poll(pfds, 1, 0) != -1) {
    if (pfds[0].revents & POLLIN) {
      readLine(line);
    }
    /* Audio here */
  }
  stopAudio(&a);
}
