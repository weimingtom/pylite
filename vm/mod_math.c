#include "root.h"
#include "mod_math.h"

py_module_t *py_math_module;

py_object_t *py_math_sin(int argc, py_object_t *argv[])
{
	py_double_t *py_result;
	double result;
	double angle;
    assert_argc(argc, 1);
    angle = cast_double(argv[0]);
    result = sin(angle);
    py_result = py_double_new(result);
    return $(py_result);
}

py_object_t *py_math_cos(int argc, py_object_t *argv[])
{
	py_double_t *py_result;
	double result;
	double angle;
	assert(argc == 1);
    angle = cast_double(argv[0]);
    result = cos(angle);
    py_result = py_double_new(result);
    return $(py_result);
}

py_object_t *py_math_pow(int argc, py_object_t *argv[])
{
	double x;
    double y;
    double result;
    py_double_t *py_result;
	assert_argc(argc, 2);
    x = cast_double(argv[0]);
    y = cast_double(argv[1]);
    result = pow(x, y);
    py_result = py_double_new(result);
    return $(py_result);
}

void py_math_module_init(void)
{
    py_math_module = py_module_new(NULL, "math");
    register_py_module(py_math_module);

    py_module_import_double(py_math_module, "pi", 3.14159265359);
    py_module_import_lambda(py_math_module, "sin", py_math_sin);
    py_module_import_lambda(py_math_module, "cos", py_math_cos);
    py_module_import_lambda(py_math_module, "pow", py_math_pow);
}
