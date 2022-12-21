#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../audio/dsp.h"
#include "parse.h"

static void eatSpace(Parsing *);
static void getFunc(Parsing *);
static void getArgs(Parsing *);

static void eatSpace(Parsing *p) {
  while (isblank(*p->remaining)) {
    p->remaining++;
  }
}

static void getFunc(Parsing *p) {
  char f = *p->remaining;
  if (isalpha(f)) {
    p->func = tolower(f);
    p->right = isupper(f);
  } else {
    p->func = F_UNKNOWN;
  }
  p->remaining++;
}

static void getArgs(Parsing *p) {
  p->args = p->remaining;
  while (*p->remaining != ';' && *p->remaining != '\n') {
    p->remaining++;
  }
  if (*p->remaining == ';') {
    *p->remaining = '\0';
    p->remaining++;
    if (*p->remaining == '\n') {
      *p->remaining = '\0';
    }
  } else {
    *p->remaining = '\0';
  }
}

Parsing parsing(char *s) {
  Parsing p = {0};
  p.remaining = s;
  return p;
}

bool isEol(Parsing *p) {
  return (*p->remaining == '\0');
}

float parseFloat(char *s) {
  return fabs(atof(s));
}

float parseBoundFloat(char *s, float max) {
  return TRUNC(parseFloat(s), max);
}

void parseFunc(Parsing *p) {
  eatSpace(p);
  getFunc(p);
  eatSpace(p);
  getArgs(p);
}
