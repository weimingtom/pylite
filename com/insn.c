#include "root.h"
#include "insn.h"

insn_t *insn_new(int opcode)
{
	int i;
    insn_t *this_ = malloc(sizeof(insn_t));
    chain_init(&this_->chain);
    this_->opcode = opcode_array + opcode;
    this_->operand_count = 0;
    for (i = 0; i < MAX_OPERAND; i++)
        this_->operand_array[i] = NULL;
    return this_;
}

void insn_delete(insn_t *this_)
{
    free(this_);
}

void insn_add_operand(insn_t *this_, operand_t *operand)
{
    this_->operand_array[this_->operand_count] = operand;
    this_->operand_count += 1;
}

operand_t *insn_get_operand(insn_t *this_, int index)
{
    assert(index < MAX_OPERAND);
    return this_->operand_array[index];
}

/** 
 * %i   immed
 * %d   integer const 
 * %f   float const 
 * %s   string const
 * %S   symbol
 * %o   operand
 **/
void insn_format(insn_t *this_, int opcode, char *format, va_list ap)
{
	char flag;
    operand_t *operand = NULL;
	if (format == NULL)
        return;

    assert(format[0] == '%');
    flag = format[1];
    
    switch (flag) {
        case 'i':
            operand = operand_immed_new(va_arg(ap, int));
            break;

        case 'd':
            operand = operand_double_new(va_arg(ap, int));
            break;

        case 'f':
            operand = operand_double_new(va_arg(ap, double));
            break;

        case 's':
            operand = operand_string_new(va_arg(ap, char *));
            break;

        case 'S':
            operand = operand_symbol_new(va_arg(ap, char *));
            break;

        case 'o':
            operand = va_arg(ap, operand_t *);
            break;

        default:
            assert(0);
    }

    insn_add_operand(this_, operand);
}
