#ifndef _COM_INSN_H
#define _COM_INSN_H

#include "opcode.h"
#include "operand.h"

#define MAX_OPERAND 4
typedef struct {
    chain_t chain;
    opcode_t *opcode;
    int operand_count;
    operand_t *operand_array[MAX_OPERAND];
} insn_t;

#define to_insn(chain) ((insn_t *)(chain))

extern insn_t *insn_new(int opcode);
extern void insn_add_operand(insn_t *this_, operand_t *operand);
extern operand_t *insn_get_operand(insn_t *this_, int index);
extern void insn_format(insn_t *this_, int opcode, char *format, va_list ap);
extern void insn_output(insn_t *this_, xml_file_t *xml_file);

#endif
