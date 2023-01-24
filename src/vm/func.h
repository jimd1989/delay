#pragma once

#define VM_EXTEND '@'

typedef enum VmFunc {
  VM_END              =  0 ,
  VM_GOTO             =  1 ,
  VM_READ             = '{',
  VM_WRITE            = '}',
  VM_AND              = '&',
  VM_OR               = '|',
  VM_NOOP             = ',',
  VM_DROP             = '#',
  VM_DUPLICATE        = '\\',
  VM_SWAP             = '~',
  VM_PLUS             = '+',
  VM_MINUS            = '-',
  VM_MULTIPLY         = '*',
  VM_DIVIDE           = '/',
  VM_POW              = '^',
  VM_MODULO           = '%',
  VM_ABS              = '`',
  VM_IF               = '?',
  VM_ELSE             = ':',
  VM_ENDIF            = ';',
  VM_MARK             = '(',
  VM_RECALL           = ')',
  VM_NOT              = '!',
  VM_LESS             = '<',
  VM_GREATER          = '>',
  VM_EQUAL            = '=',
  VM_SINE             = '$',
  VM_VAR_A_PARAM      = 'a',
  VM_VAR_B_PARAM      = 'b',
  VM_VAR_C_PARAM      = 'c',
  VM_VAR_FEEDBACK     = 'f',
  VM_VAR_HEAP         = 'H',
  VM_VAR_TAPE_LENGTH  = 'l',
  VM_VAR_CHAN         = 'n',
  VM_VAR_PAN          = 'p',
  VM_VAR_PHASE        = 'P',
  VM_VAR_RANDOM       = 'r',
  VM_VAR_STACK_SIZE   = 's',
  VM_VAR_DELAY_TIME   = 't',
  VM_VAR_TAPE         = 'T',
  VM_VAR_VOLUME       = 'v',
  VM_VAR_WETNESS      = 'w',
  VM_VAR_SAMPLE       = 'x',
  VM_VAR_OTHER_SAMPLE = 'y',
  VM_VAR_RATE         = 'z'
} VmFunc;

/* Unused: [ ] */

typedef enum VmFuncEx {
  VM_EX_LERP    = '{',
  VM_EX_PAN     = '\\',
  VM_EX_FLOOR   = '<',
  VM_EX_CEILING = '>',
  VM_EX_AND     = '&',
  VM_EX_OR      = '|',
  VM_EX_XOR     = '^',
  VM_EX_NOT     = '~',
  VM_EX_SHIFTL  = '[',
  VM_EX_SHIFTR  = ']'
} VmFuncEx;
