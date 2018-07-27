#include "root.h"
#include "operand.h"
#include "lambda.h"

operand_t *operand_none;
operand_t *operand_true;
operand_t *operand_false;
operand_t *operand_stack;

operand_t *operand_new(int type)
{
    operand_t *this_ = malloc(sizeof(operand_t));
    this_->type = type;
    return this_;
}

void operand_consts_init(void)
{
    operand_none = operand_new(OPERAND_NONE);
    operand_true = operand_new(OPERAND_TRUE);
    operand_false = operand_new(OPERAND_FALSE);
    operand_stack = operand_new(OPERAND_STACK);
}

operand_t *operand_immed_new(int immed)
{
    operand_t *this_ = operand_new(OPERAND_IMMED);
    this_->ivalue = immed;
    return this_;
}

operand_t *operand_double_new(double dvalue)
{
    operand_t *this_ = operand_new(OPERAND_DOUBLE);
    this_->dvalue = dvalue;
    return this_;
}

operand_t *operand_string_new(char *svalue)
{
    operand_t *this_ = operand_new(OPERAND_STRING);
    this_->svalue = strdup(svalue);
    return this_;
}

operand_t *operand_symbol_new(char *name)
{
    operand_t *this_ = operand_new(OPERAND_SYMBOL);
    this_->svalue = strdup(name);
    return this_;
}

operand_t *operand_global_new(char *name)
{
    operand_t *this_ = operand_new(OPERAND_GLOBAL);
    this_->svalue = strdup(name);
    return this_;
}

operand_t *operand_local_new(int offset)
{
    operand_t *this_ = operand_new(OPERAND_LOCAL);
    this_->ivalue = offset;
    return this_;
}

operand_t *operand_item_new(void)
{
    operand_t *this_ = operand_new(OPERAND_ITEM);
    return this_;
}

operand_t *operand_field_new(char *name)
{
    operand_t *this_ = operand_new(OPERAND_FIELD);
    this_->svalue = strdup(name);
    return this_;
}

operand_t *operand_label_new(char *name)
{
    operand_t *this_ = operand_new(OPERAND_LABEL);
    this_->svalue = strdup(name);
    return this_;
}

int operand_is_memory(operand_t *this_)
{
    switch (this_->type) {
        case OPERAND_GLOBAL:
        case OPERAND_LOCAL:
        case OPERAND_ITEM:
        case OPERAND_FIELD:
            return 1;
    }
    return 0;
}


