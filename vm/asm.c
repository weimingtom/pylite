#include "root.h"
#include "lambda.h"
#include "opcode.h"
#include "double.h"
#include "symbol.h"
#include "string_.h"
#include "bool.h"
#include "none.h"
#include "gc.h"
#include "asm.h"

void py_lambda_build_label_vector(py_lambda_t *this_, xml_tree_t *xml_root)
{
	int pc = 0;
    int i;
    insn_t insn;
    int j;
    int label_count = xml_tree_find_ivalue(xml_root, "label_count");
    vector_init(&this_->label_vector);
    for (j = 0; j < label_count; j++)
        vector_push_back(&this_->label_vector, 0);

    vector_each (&this_->insn_vector, i, insn) {
        if (insn.opcode == OP_LABEL) {
            int operand;
			xml_token_t *xml_operand = insn.operand;
            assert(xml_operand->svalue[0] == 'L');
            operand = atoi(xml_operand->svalue + 1);
            vector_set(&this_->label_vector, operand, pc);
        }
        pc += insn.size;
    }
}

void py_lambda_add_code(py_lambda_t *this_, char code)
{
    vector_push_back(&this_->code_vector, code);
}

void py_lambda_build_code(py_lambda_t *this_, insn_t *insn)
{
	int operand;
    int opcode = insn->opcode;
    py_lambda_add_code(this_, opcode);
    if (insn->operand == NULL)
        return;
    operand = py_lambda_build_operand(this_, insn->operand);
    py_lambda_add_code(this_, operand & 0xFF);
    py_lambda_add_code(this_, (operand >> 8) & 0xFF);
}

void py_lambda_build_code_vector(py_lambda_t *this_)
{
    int pc = 0;
    int i;
    insn_t insn;
    vector_init(&this_->code_vector);

    vector_each (&this_->insn_vector, i, insn) {
        if (insn.opcode == OP_LABEL)
            continue;
        py_lambda_build_code(this_, &insn);
        pc += insn.size;
    }
}

int py_lambda_build_operand(py_lambda_t *this_, xml_token_t *xml_operand)
{
	int value;
	char prefix;
    if (xml_operand->type == XML_TOKEN_DOUBLE)
        return (int)xml_operand->dvalue;

    assert(xml_operand->type == XML_TOKEN_SYMBOL);
    prefix = xml_operand->svalue[0];
    assert(prefix == 'L' || prefix == 'c');

    value = atoi(xml_operand->svalue + 1);
    if (prefix == 'L')
        value = vector_get(&this_->label_vector, value);
    return value;
}

void py_lambda_build_insn(py_lambda_t *this_, xml_tree_t *xml_insn)
{
    insn_t insn;
    xml_token_t *xml_opcode = xml_tree_get_token(xml_insn, 0);
    opcode_t *opcode = lookup_opcode(xml_opcode->svalue);

    insn.opcode = opcode->id;
    insn.size = opcode->size;
    if (xml_insn->token_vector.count == 2) {
        insn.operand = xml_tree_get_token(xml_insn, 1);
    } else {
        insn.operand = NULL;
    }
    vector_push_back(&this_->insn_vector, insn);
}

void py_lambda_build_insn_vector(py_lambda_t *this_, xml_tree_t *xml_root)
{
    int i;
    xml_tree_t *xml_insn;
    xml_tree_t *xml_insn_vector;
    vector_init(&this_->insn_vector);
    xml_insn_vector = xml_tree_find_child(xml_root, "insn_vector");

    vector_each (&xml_insn_vector->child_vector, i, xml_insn) {
        py_lambda_build_insn(this_, xml_insn);
    }
}

void py_lambda_assemble(py_lambda_t *this_, xml_tree_t *xml_root)
{
    py_lambda_build_insn_vector(this_, xml_root);
    py_lambda_build_label_vector(this_, xml_root);
    py_lambda_build_code_vector(this_);
}
