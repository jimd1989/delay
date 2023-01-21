#include <stdbool.h>
#include <stdlib.h>

#include "../input/variables.h"
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

Vm vm(Variables *v) {
  Vm vm = {0};
  vm.programA = program();
  vm.programB = program();
  vm.program = &vm.programA;
  vm.programOld = &vm.programB;
  vm.interpreter = interpreter(v, vm.program);
  vm.compiler = compiler(vm.programOld);
  return vm;
}
