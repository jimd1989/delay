#include <stdbool.h>
#include <stdlib.h>

#include "compiler.h"
#include "interpreter.h"
#include "program.h"
#include "vm.h"

void setVmProgram(Vm *v, char *s) {
  Program *p = NULL;
  if (compile(&v->compiler, s, true)) {
    p = v->programOld;
    v->programOld = v->program;
    v->program = p;
    setInterpreterProgram(&v->interpreter, v->program);
    setCompilerProgram(&v->compiler, v->programOld);
  }
  /* Need failed compilation input cleanup */
}

Vm vm(void) {
  /* Constructor should take Variables struct */
  Vm v = {0};
  v.programA = program();
  v.programB = program();
  v.program = &v.programA;
  v.programOld = &v.programB;
  v.interpreter = interpreter(v.program);
  v.compiler = compiler(v.programOld);
  return v;
}
