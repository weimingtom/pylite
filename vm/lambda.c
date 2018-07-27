#include "root.h"
#include "lambda.h"
#include "opcode.h"
#include "double.h"
#include "symbol.h"
#include "string_.h"
#include "bool.h"
#include "none.h"
#include "asm.h"
#include "gc.h"

py_class_t *py_lambda_class;

static void *load_const(py_module_t *py_module, xml_tree_t *xml_root)
{
    xml_token_t *xml_token = xml_tree_get_token(xml_root, 0);
    char *symbol;

    switch (xml_token->type) {
        case XML_TOKEN_DOUBLE:
            return py_double_new(xml_token->dvalue);

        case XML_TOKEN_SYMBOL:
            symbol = xml_token->svalue;
            if (strcmp(symbol, "lambda") == 0)
                return py_lambda_load(py_module, xml_root); 
            if (strcmp(symbol, "None") == 0)
                return py_none;
            if (strcmp(symbol, "True") == 0)
                return py_true;
            if (strcmp(symbol, "False") == 0)
                return py_false;
            return py_symbol_new(symbol);

        case XML_TOKEN_STRING:
            return py_string_new(xml_token->svalue);

        default:
            assert(0);
    }

    return NULL;
}

void py_lambda_build_const_vector(py_lambda_t *this_, 
     py_module_t *py_module, xml_tree_t *xml_root)
{
    int i;
    xml_tree_t *xml_const;
    xml_tree_t *xml_const_vector;

    vector_init(&this_->const_vector);
    xml_const_vector = xml_tree_find_child(xml_root, "const_vector");
    vector_each(&xml_const_vector->child_vector, i, xml_const) {
        py_object_t *py_const = load_const(py_module, xml_const);
        vector_push_back(&this_->const_vector, py_const);
    }
}

void py_lambda_build_guard(py_lambda_t *this_, xml_tree_t *xml_guard)
{
    xml_token_t *xml_start = xml_tree_find_value(xml_guard, "start");
    int start = py_lambda_build_operand(this_, xml_start);

    xml_token_t *xml_end = xml_tree_find_value(xml_guard, "end");
    int end = py_lambda_build_operand(this_, xml_end);

    xml_token_t *xml_handler = xml_tree_find_value(xml_guard, "handler");
    int handler = py_lambda_build_operand(this_, xml_handler);

    guard_t guard;
    guard.start = start;
    guard.end = end;
    guard.handler = handler;
    vector_push_back(&this_->guard_vector, guard);
}

static int sort_by_end(const void *a, const void *b)
{
    guard_t *p = $(a);
    guard_t *q = $(b);
    return p->end - q->end;
}

void py_lambda_build_guard_vector(py_lambda_t *this_, xml_tree_t *xml_root)
{
    int i;
    xml_tree_t *xml_guard;
    xml_tree_t *xml_guard_vector;

    vector_init(&this_->guard_vector);
    xml_guard_vector = xml_tree_find_child(xml_root, "guard_vector");
    vector_each(&xml_guard_vector->child_vector, i, xml_guard) {
        py_lambda_build_guard(this_, xml_guard);
    }

    qsort(this_->guard_vector.data, this_->guard_vector.count, 
          sizeof(guard_t), sort_by_end);
}

void py_lambda_build_line_number_map(py_lambda_t *this_, xml_tree_t *xml_root)
{
	int i;
    xml_token_t *xml_token;
    xml_tree_t *xml_map;
    vector_init(&this_->line_number_map);
    xml_map = xml_tree_find_child(xml_root, "line_number_map");
    assert(xml_map);

    assert(xml_map->token_vector.count - 1 == this_->insn_vector.count);

    vector_each (&xml_map->token_vector, i, xml_token) {
        short line_number;
		insn_t *insn;
		int j;
		if (i == 0)
            continue;
        assert(xml_token->type == XML_TOKEN_DOUBLE);
        line_number = (short) xml_token->dvalue;

        insn = this_->insn_vector.data + i;
        for (j = 0; j < insn->size; j++)
            vector_push_back(&this_->line_number_map, line_number);
    }
}

py_lambda_t *py_lambda_load(py_module_t *py_module, xml_tree_t *xml_root)
{
	char *name;
    py_lambda_t *this_ = py_object_alloc(sizeof(py_lambda_t), py_lambda_class);
    gc_add_root($(this_));

    this_->py_module = py_module;
    name = xml_tree_find_svalue(xml_root, "name");
    this_->name = strdup(name);

    this_->local_count = xml_tree_find_ivalue(xml_root, "local_count");
    this_->param_count = xml_tree_find_ivalue(xml_root, "param_count");
    py_lambda_assemble(this_, xml_root);
    py_lambda_build_guard_vector(this_, xml_root);
    py_lambda_build_line_number_map(this_, xml_root);
    py_lambda_build_const_vector(this_, py_module, xml_root);
    return this_;
}

static int load_short(char *pc)
{
    unsigned char *p = (unsigned char *)pc;
    return (short)(p[0] + (p[1] << 8));
}

void py_lambda_dump(py_lambda_t *this_, xml_file_t *xml_file)
{
    char *pc = this_->code_vector.data;
    char *end = pc + this_->code_vector.count;

    xml_file_push(xml_file);
    while (pc < end) {
        opcode_t *opcode = opcode_array + ((int)*pc);
        xml_file_indent(xml_file);
        xml_file_printf(xml_file, "%s", opcode->name);
        if (opcode->size == 3) {
            int operand = load_short(pc + 1);
            xml_file_printf(xml_file, " %d\n", operand);
        } else {
            xml_file_printf(xml_file, "\n");
        }
        pc += opcode->size;
    }
    xml_file_pop(xml_file);
}

guard_t *py_lambda_locate_guard(py_lambda_t *this_, int pc)
{
    int i;
    guard_t *guard;

    vector_each_address (&this_->guard_vector, i, guard) {
        if (guard->start <= pc && pc < guard->end)
            return guard;
    }
    return NULL;
}

void py_lambda_mark(py_lambda_t *this_)
{
    int i;
    py_object_t *py_const;
    vector_each (&this_->const_vector, i, py_const)
        gc_mark(py_const);
}

void py_lambda_class_init()
{
    py_lambda_class = py_class_new("lambda");
    py_lambda_class->gc_mark = $(py_lambda_mark);
}
