#pragma once

#include <stdint.h>

#include "array.h"
#include "func.h"

typedef enum VmCellType {
  VM_CELL_EMPTY = 0,
  VM_CELL_FUNC,
  VM_CELL_EX_FUNC,
  VM_CELL_NUM
} VmCellType;

typedef union VmCellData {
  VmFunc          f;
  VmFuncEx        g;
  float           n;
  int64_t         i;
  Array         * p;
} VmCellData;

typedef struct VmCell {
  VmCellType    type;
  VmCellData    data;
} VmCell;

char *parseCell(VmCell *, char *);
VmCell endProgram(void);
VmCell number(float);
VmCell address(Array *);
VmCell cell(void);
