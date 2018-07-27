#include <string.h>
#include "root.h"
#include "lambda.h"
#include "trace.h"

lambda_t *lambda_new(char *name)
{
    lambda_t *this_ = malloc(sizeof(lambda_t));

    this_->type = OPERAND_LAMBDA;
    this_->name = name ? strdup(name) : NULL;
    this_->param_count = 0;
    this_->local_count = 0;
    this_->label_count = 0;

    list_init(&this_->insn_list);
    stack_init(&this_->break_stack);
    stack_init(&this_->continue_stack);
    stack_init(&this_->finally_stack);

    vector_init(&this_->const_vector);
    vector_init(&this_->guard_vector);
    vector_init(&this_->line_number_map);
    return this_;
}

void lambda_emit_insn(lambda_t *this_, int opcode, char *format, ...)
{
	insn_t *insn;
    va_list ap;
    int line_number = ast_stack_top()->line_number;
    vector_push_back(&this_->line_number_map, line_number);

    insn = insn_new(opcode);
    list_push_back(&this_->insn_list, insn);

    va_start(ap, format);
    insn_format(insn, opcode, format, ap);
    va_end(ap);
}

int lambda_new_local(lambda_t *this_)
{
    this_->local_count++;
    return 0 - this_->local_count;
}

void lambda_emit_label(lambda_t *this_, operand_t *label)
{
    lambda_emit_insn(this_, OP_LABEL, "%o", label); 
}

operand_t *lambda_new_label(lambda_t *this_)
{
    operand_t *label;
	char text[64];

    sprintf(text, "L%d", this_->label_count);
    label = operand_label_new(text);
    this_->label_count++;
    return label;
}

static int compare_const(operand_t *old_const, operand_t *new_const)
{
    if (old_const->type != new_const->type)
        return 0;

    switch (old_const->type) {
        case OPERAND_IMMED:
        case OPERAND_LOCAL:
            return old_const->ivalue == new_const->ivalue;

        case OPERAND_DOUBLE:
            return old_const->dvalue == new_const->dvalue;

        case OPERAND_GLOBAL:
        case OPERAND_STRING:
        case OPERAND_SYMBOL:
            return strcmp(old_const->svalue, new_const->svalue) == 0;

        case OPERAND_NONE:
        case OPERAND_TRUE:
        case OPERAND_FALSE:
            return 1;

        case OPERAND_LAMBDA:
            return 0;

        default:
            assert(0); 
    }
    return 0;
}

int lambda_add_const(lambda_t *this_, operand_t *new_const)
{
    int index;
	int i;
    operand_t *old_const;

    vector_each (&this_->const_vector, i, old_const) {
        int is_same = compare_const(old_const, new_const); 
        if (is_same)
            return i;
    }

    index = this_->const_vector.count;
    vector_push_back(&this_->const_vector, new_const);
    return index;
}

void lambda_output_operand(lambda_t *this_, operand_t *operand, xml_file_t *xml_file)
{
    int const_index;

    switch (operand->type) {
        case OPERAND_DOUBLE:
        case OPERAND_STRING:
        case OPERAND_SYMBOL:
        case OPERAND_LAMBDA:
        case OPERAND_NONE:
        case OPERAND_TRUE:
        case OPERAND_FALSE:
            const_index = lambda_add_const(this_, operand);
            xml_file_printf(xml_file, " c%d", const_index);
            break;

        case OPERAND_IMMED:
        case OPERAND_LOCAL:
            xml_file_printf(xml_file, " %d", operand->ivalue);
            break;

        case OPERAND_LABEL:
            xml_file_printf(xml_file, " %s", operand->svalue); 
            break;

        default:
            assert(0);
    }
}

void lambda_output_insn(lambda_t *this_, insn_t *insn, xml_file_t *xml_file)
{
	int i;
    xml_file_indent(xml_file);
    xml_file_printf(xml_file, "%s", insn->opcode->name);
    for (i = 0; i < insn->operand_count; i++) {
        operand_t *operand = insn->operand_array[i];
        lambda_output_operand(this_, operand, xml_file);
    }
    xml_file_printf(xml_file, "\n");
}

void lambda_output_code(lambda_t *this_, xml_file_t *xml_file)
{
    chain_t *chain;
    xml_file_dump(xml_file, "insn_vector");
    xml_file_push(xml_file);
    list_each (&this_->insn_list, chain) {
        insn_t *insn = to_insn(chain);
        lambda_output_insn(this_, insn, xml_file);
    }
    xml_file_pop(xml_file);
}

void lambda_output_const(lambda_t *this_, operand_t *operand, xml_file_t *xml_file)
{
    lambda_t *lambda;
    switch (operand->type) {
        case OPERAND_LAMBDA:
            lambda = (lambda_t *) operand;
            lambda_output(lambda, xml_file);
            break;

        case OPERAND_DOUBLE:
            xml_file_dump(xml_file, "%lf", operand->dvalue);
            break;

        case OPERAND_STRING:
            xml_file_dump(xml_file, "\"%s\"", operand->svalue);
            break;

        case OPERAND_SYMBOL:
            xml_file_dump(xml_file, "%s", operand->svalue);
            break;

        case OPERAND_NONE:
            xml_file_dump(xml_file, "None");
            break;

        case OPERAND_TRUE:
            xml_file_dump(xml_file, "True");
            break;

        case OPERAND_FALSE:
            xml_file_dump(xml_file, "False");
            break;

        default:
            assert(0);
    }
}

void lambda_output_const_vector(lambda_t *this_, xml_file_t *xml_file)
{
    int i;
    operand_t *operand;
    xml_file_dump(xml_file, "const_vector");
    xml_file_push(xml_file);

    vector_each (&this_->const_vector, i, operand)
        lambda_output_const(this_, operand, xml_file);

    xml_file_pop(xml_file);
}

void lambda_output_guard(lambda_t *this_, guard_t *guard, xml_file_t *xml_file)
{
    xml_file_dump(xml_file, "guard");
    xml_file_push(xml_file);

    xml_file_dump(xml_file, "start %s", guard->start->svalue);
    xml_file_dump(xml_file, "end %s", guard->end->svalue);
    xml_file_dump(xml_file, "handler %s", guard->handler->svalue);

    xml_file_pop(xml_file);
}

void lambda_output_guard_vector(lambda_t *this_, xml_file_t *xml_file)
{
    int i;
    guard_t guard;
    xml_file_dump(xml_file, "guard_vector");
    xml_file_push(xml_file);

    vector_each (&this_->guard_vector, i, guard)
        lambda_output_guard(this_, &guard, xml_file);

    xml_file_pop(xml_file);
}

void lambda_output_line_number_map(lambda_t *this_, xml_file_t *xml_file)
{
    int i;
    int line_number;
    xml_file_indent(xml_file);
    xml_file_printf(xml_file, "line_number_map");

    vector_each (&this_->line_number_map, i, line_number)
        xml_file_printf(xml_file, " %d", line_number);

    xml_file_printf(xml_file, "\n");
}

void lambda_output(lambda_t *this_, xml_file_t *xml_file)
{
    xml_file_dump(xml_file, "lambda");
    xml_file_push(xml_file);
    xml_file_dump(xml_file, "name %s", this_->name);
    xml_file_dump(xml_file, "param_count %d", this_->param_count);
    xml_file_dump(xml_file, "local_count %d", this_->local_count);
    xml_file_dump(xml_file, "label_count %d", this_->label_count);
    lambda_output_code(this_, xml_file);
    lambda_output_const_vector(this_, xml_file);
    lambda_output_guard_vector(this_, xml_file);
    lambda_output_line_number_map(this_, xml_file);
    xml_file_pop(xml_file);
}
