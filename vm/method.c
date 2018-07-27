#include "root.h"
#include "method.h"
#include "lambda.h"
#include "native.h"
#include "gc.h"

py_class_t *py_method_class;

void py_method_mark(py_method_t *this_)
{
    gc_mark(this_->py_object);
    gc_mark(this_->py_callable);
}

void py_method_class_init()
{
    py_method_class = py_class_new("method");
    py_method_class->gc_mark = $(py_method_mark);
}

py_method_t *py_method_new(py_object_t *py_object, py_object_t *py_callable)
{
    py_method_t *this_ = py_object_alloc(sizeof(py_method_t), py_method_class);
    this_->py_object = py_object;
    this_->py_callable = py_callable;
    return this_;
}
