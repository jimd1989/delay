#pragma once

#include "func.h"

typedef enum VmCellType {
  VM_CELL_EMPTY = 0,
  VM_CELL_FUNC,
  VM_CELL_NUM
} VmCellType;

typedef union VmCellData {
  VmFunc        f;
  float         n;
} VmCellData;

typedef struct VmCell {
  VmCellType    type;
  VmCellData    data;
} VmCell;
