#include "root.h"
#include "slice.h"
#include "cast.h"

py_class_t *py_slice_class;

py_slice_t *py_slice_new(int argc, py_object_t *argv[])
{
	py_slice_t *this_;
	py_object_t *start;
    py_object_t *stop;
	assert_argc(argc, 2);
    start = argv[0];
    stop = argv[1];

    this_ = py_object_alloc(sizeof(py_slice_t), py_slice_class);
    this_->start = start;
    this_->stop = stop;
    py_object_set_field($(this_), py_symbol_start, start);
    py_object_set_field($(this_), py_symbol_stop, stop);
    return this_;
}

void py_slice_class_init()
{
    py_slice_class = py_class_new("slice");
}

py_object_t *py_slice_parse(py_slice_t *this_, int *_start, int *_stop, int size)
{
    int stop;
    int start = cast_integer(this_->start);
    if (start < 0)
        vm_throw(py_index_error);

    if (this_->stop == py_none) {
        stop = size;
    } else {
        stop = cast_integer(this_->stop);
        if (stop < 0)
            stop += size;
    }

    if (start > stop)
        vm_throw(py_index_error);

    *_start = start;
    *_stop = stop;
    return NULL;
}
