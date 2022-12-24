#include <ctype.h>
#include <err.h>
#include <stdbool.h>
#include <unistd.h>

#include "cell.h"
#include "program.h"

#define IS_EOL(S) (*(S) == '\n' || *(S) == '\0')

static char *eatWhitespace(char *s);

static char *eatWhitespace(char *s) {
  while (isblank(*s)) {
    s++;
  }
  return s;
}

bool loadProgram(Program *p, char *s) {
  size_t n = 0;
  while (!IS_EOL(s)) {
    if (n >= PROGRAM_SIZE) {
      warnx("program exceeds limit of %u", (unsigned int)PROGRAM_SIZE);
      return false;
    }
    s = eatWhitespace(s);
    s = parseCell(&p->data[n++], s);
  }
  p->size = n;
  return true;
}

Program program(void) {
  Program p = {0};
  return p;
}
