#pragma once

#include <stdbool.h>

typedef enum FuncName {
  F_UNKNOWN    = 0,
  F_DELAY_FUNC = 'd',
  F_FEEDBACK   = 'f',
  F_MIX_FUNC   = 'm',
  F_PAN        = 'p',
  F_RECORD_VOL = 'r',
  F_DELAY_TIME = 't',
  F_VOL        = 'v',
  F_WET        = 'w'
} FuncName;

typedef struct Parsing {
  bool            right;
  FuncName        func;
  char          * args;
  char          * remaining;
} Parsing;

bool isEol(Parsing *);
float parseFloat(char *);
float parseBoundFloat(char *, float);
void parseFunc(Parsing *);
Parsing parsing(char *);
