#pragma once

#include <unistd.h>

#define STACK_SIZE (size_t)64

typedef struct Stack {
  size_t        size;
  size_t        head;
  VmCell        data[STACK_SIZE];
} Stack;

float *directNumber(Stack *);
VmCell popStack(Stack *);
void pushStack(Stack *, VmCell);
Stack stack(void);
