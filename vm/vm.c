#include "root.h"
#include "vm.h"
#include "mod_builtin.h"
#include "opcode.h"
#include "objects.h"
#include "error.h"
#include "gc.h"

py_object_t *vm_stack[VM_STACK_DEPTH];
int sp = VM_STACK_DEPTH;

static __inline py_object_t *py_range_next_fast(py_range_t *this_)
{
	py_double_t *py_item;
    if (this_->cursor == this_->end)
        vm_throw(py_stop_iteration);
    py_item = py_double_new(this_->cursor);
    this_->cursor += this_->step;
    return $(py_item);
}

static __inline int load_short(char *pc)
{
    unsigned char *p = (unsigned char *)pc;
    return (short)(p[0] + (p[1] << 8));
}

static __inline py_object_t *unary_op(int opcode, arguments)
{
	py_object_t *py_object;
    assert(argc == 1);
    py_object = argv[0];

    if (py_object_is_double(py_object)) {
        py_double_t *target;
		int value = (int) ((py_double_t *)py_object)->value;
        switch (opcode) {
            case OP_COM:
                value = ~value;
                break;

            case OP_NEG:
                value = -value;
                break;
        }
        target = py_double_new(value);
        return $(target);
    } else {
        vm_throw(py_type_error);
    }
    assert(0);
}

static __inline py_object_t *integer_op_integer(int opcode, arguments)
{
    py_object_t *py_left;
    py_object_t *py_right;
	assert(argc == 2);
    py_left = argv[0];
    py_right = argv[1];

    if (py_object_is_double(py_left) && py_object_is_double(py_right)) {
        py_double_t *target;
		int lvalue = (int) ((py_double_t *)py_left)->value;
        int rvalue = (int) ((py_double_t *)py_right)->value;
        int value = 0;
        switch (opcode) {
            case OP_XOR:
                value = lvalue ^ rvalue;
                break;

            case OP_AND:
                value = lvalue & rvalue;
                break;

            case OP_OR:
                value = lvalue | rvalue;
                break;

            case OP_LSH:
                value = lvalue << rvalue;
                break;

            case OP_RSH:
                value = lvalue >> rvalue;
                break;
        }
        target = py_double_new(value);
        return $(target);
    } else {
        vm_throw(py_type_error);
    }
}

static __inline py_object_t *double_op_double(int opcode, arguments)
{
    py_object_t *py_left;
    py_object_t *py_right;
	assert(argc == 2);
    py_left = argv[0];
    py_right = argv[1];

    if (py_object_is_double(py_left)) { 
        double value;
		double lvalue;
        double rvalue;
		if (!py_object_is_double(py_right))
            vm_throw(py_type_error);
        lvalue = ((py_double_t *)py_left)->value;
        rvalue = ((py_double_t *)py_right)->value;

        value = 0;
        switch (opcode) {
            case OP_ADD:
                value = lvalue + rvalue;
                break;

            case OP_SUB:
                value = lvalue - rvalue; 
                break;

            case OP_MUL:
                value = lvalue * rvalue; 
                break;

            case OP_DIV:
                if (rvalue == 0)
                    vm_throw(py_zero_division_error);
                value = lvalue / rvalue; 
                break;

            case OP_MOD:
                value = fmod(lvalue, rvalue); 
                break;
        }
        return $(py_double_new(value));
    } else {
		py_object_t *py_field;
		py_class_t *py_class;
        py_symbol_t *py_symbol;
        switch (opcode) {
            case OP_ADD:
                py_symbol = py_symbol__add__;
                break;

            case OP_SUB:
                py_symbol = py_symbol__sub__;
                break;

            case OP_MUL:
                py_symbol = py_symbol__mul__;
                break;

            case OP_DIV:
                py_symbol = py_symbol__div__;
                break;

            case OP_MOD:
                py_symbol = py_symbol__mod__;
                break;
        }
        py_class = py_left->py_class;
        py_field = py_class_load_field(py_class, py_symbol);
        if (py_field == NULL)
            vm_throw(py_attr_error);
        return vm_call(py_field, 2, argv);
    }
}

static __inline int compute_bool(py_object_t *py_object)
{
    py_class_t *py_class = py_object->py_class;

    if (py_class == py_double_class) {
        py_double_t *py_double = $(py_object);
        return py_double->value != 0;
    }

    if (py_class == py_none_class) {
        return 0;
    }

    if (py_class == py_bool_class) {
        if (py_object == py_true)
            return 1;
        if (py_object == py_false)
            return 0;
        assert(0);
    }

    if (py_class == py_string_class) {
        py_string_t *py_string = $(py_object);
        return strlen(py_string->value) > 0;
    }

    return 1;
}

static __inline int jcompare(int opcode, arguments)
{
    py_object_t *py_left = argv[0];
    py_object_t *py_right = argv[1];

    if (py_object_is_double(py_left)) { 
        double rvalue;
		double lvalue;
		if (!py_object_is_double(py_right))
            vm_throw_double(py_type_error);

        lvalue = ((py_double_t *)py_left)->value;
        rvalue = ((py_double_t *)py_right)->value;
        switch (opcode) {
            case OP_JLE:
                return lvalue <= rvalue;

            case OP_JLT:
                return lvalue < rvalue;

            case OP_JNE:
                return lvalue != rvalue;

            case OP_JEQ:
                return lvalue == rvalue;

            case OP_JGT:
                return lvalue > rvalue;

            case OP_JGE:
                return lvalue >= rvalue;
        }
    } else {
		int ok;
        py_class_t *py_class;
        py_object_t *py_field;
		py_object_t *py_bool;
        py_symbol_t *py_symbol;
        switch (opcode) {
            case OP_JLE:
                py_symbol = py_symbol__le__;
                break;

            case OP_JLT:
                py_symbol = py_symbol__lt__;
                break;

            case OP_JNE:
                py_symbol = py_symbol__ne__;
                break;

            case OP_JEQ:
                py_symbol = py_symbol__eq__;
                break;

            case OP_JGT:
                py_symbol = py_symbol__gt__;
                break;

            case OP_JGE:
                py_symbol = py_symbol__ge__;
                break;
        }
        py_class = py_left->py_class;
        py_field = py_class_load_field(py_class, py_symbol);
        if (py_field == NULL)  // Ignore the error!
            return 0;
        py_bool = vm_call(py_field, 2, argv);
        if (py_bool == NULL)  // Ignore the error!
            return 0;
        ok = compute_bool(py_bool);
        return ok;
    }

    assert(0);
    return 0;
}

py_object_t *vm_call_class(py_class_t *py_class, arguments)
{
	py_object_t *py_result;
	py_object_t *py_init;
    py_object_t *py_instance;
    if (py_class->py_alloc)
        py_instance = py_class->py_alloc(py_class);
    else
        py_instance = py_object_alloc(sizeof(py_object_t), py_class);

    py_init = py_object_get_field($(py_class), py_symbol__init__);
    if (py_init == NULL)
        return py_instance;

    vm_stack_push(py_instance);
    py_result = vm_call(py_init, argc + 1, argv - 1);
    vm_stack_pop();

    if (py_result == NULL)
        vm_rethrow();
    return py_instance;
}

py_object_t *vm_call_method(py_method_t *py_method, arguments)
{
	py_object_t *py_result;
    py_object_t *py_instance = py_method->py_object;
    py_object_t *py_callable = py_method->py_callable;
    vm_stack_push(py_instance);
    py_result = vm_call(py_callable, argc + 1, argv - 1);
    vm_stack_pop();
    return py_result;
}

void vm_alloc_local(py_lambda_t *py_lambda)
{
	int i;
    int bp = sp;
    sp -= py_lambda->local_count;
    for (i = sp; i < bp; i++)
        vm_stack[i] = py_none;
}

#define TRACE 0
py_object_t *vm_call_lambda(py_lambda_t *py_lambda, arguments)
{
	int bp;
	py_module_t *py_module;
	py_object_t **const_vector;
	char *py_code_vector;
	int pc;
    assert(py_lambda->py_class == py_lambda_class);
    if (py_lambda->param_count != argc)
        vm_throw(py_type_error);
    bp = sp;

    py_module = py_lambda->py_module;
    const_vector = py_lambda->const_vector.data;
    py_code_vector = py_lambda->code_vector.data;
    pc = 0;
    vm_alloc_local(py_lambda);

    while (1) {
        int opcode = (int) py_code_vector[pc];
#if TRACE
        fprintf(stderr, "%s\n", opcode_array[opcode].name);
#endif
        switch (opcode) {
            #include "dispatch.h"
        }
    }

    return NULL;
}

static __inline py_object_t *vm_call_native(py_native_t *py_native, arguments)
{
    handler_t handler = py_native->handler;
    return handler(argc, argv);
}

py_object_t *vm_call(py_object_t *py_callee, arguments)
{
    py_class_t *py_class = py_callee->py_class;

    if (py_class == NULL)
        return vm_call_class($(py_callee), argc, argv);
    if (py_class == py_lambda_class)
        return vm_call_lambda($(py_callee), argc, argv);
    if (py_class == py_method_class)
        return vm_call_method($(py_callee), argc, argv);
    if (py_class == py_native_class)
        return vm_call_native($(py_callee), argc, argv);

    assert(0);
    return NULL;
}
