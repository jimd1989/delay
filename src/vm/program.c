#include <err.h>

#include "cell.h"
#include "program.h"

void resetProgram(Program *p) {
  p->head = 0;
}

VmCell *nextProgramCell(Program *p, bool verbose) {
  if (p->head >= p->size) {
    if (verbose) {
      warnx("program size exceeds %u instructions", (unsigned int)p->size);
    }
    return NULL;
  } 
  return &p->data[p->head++];
}

Program program(void) {
  Program p = {0};
  p.size = PROGRAM_SIZE;
  return p;
}
