#include "root.h"
#include "class.h"
#include "native.h"
#include "gc.h"

py_class_t *py_class_new(char *name)
{
    py_class_t *this_ = py_object_alloc(sizeof(py_class_t), NULL);
    gc_add_root($(this_));

    this_->name = strdup(name);
    this_->py_alloc = NULL;
    this_->gc_mark = NULL;
    this_->gc_free = NULL;
    this_->parent = NULL;
    return this_;
}

int py_class_is_subclass(py_class_t *this_, py_class_t *parent)
{
    py_class_t *py_class = this_;
    while (py_class != NULL) {
        if (py_class == parent)
            return 1;
        py_class = py_class->parent;
    }
    return 0;
}

py_object_t *py_class_load_field(py_class_t *this_, py_symbol_t *name)
{
    py_object_t *result = py_object_get_field($(this_), name);
    if (result)
        return result;

    if (this_->parent == NULL)
        return NULL;
    return py_class_load_field(this_->parent, name);
}

void py_class_register_natives(py_class_t *this_, native_t *natives)
{
	native_t *native;
    for (native = natives; native->name; native++) {
        py_symbol_t *name = py_symbol_new(native->name); 
        void *handler = native->handler;

        py_native_t *py_native = py_native_new(name, handler);
        py_object_set_field($(this_), name, $(py_native));
    }
}
