#include "root.h"
#include "range.h"
#include "cast.h"

py_class_t *py_range_class;

py_object_t *py_range_alloc(py_class_t *py_class)
{
    py_range_t *this_ = py_object_alloc(sizeof(py_range_t), py_class);
    this_->start = 0;
    this_->end = 0;
    this_->step = 1;
    this_->cursor = 0;
    return $(this_);
}

py_object_t *py_range_init(int argc, py_object_t *argv[])
{
	py_range_t *this_;
    int start = 0;
    int end = 0;
    int step = 1;
   
    switch (argc) {
        case 2:
            end = cast_integer(argv[1]);
            break;

        case 3:
            start = cast_integer(argv[1]);
            end = cast_integer(argv[2]);
            break;

        case 4:
            start = cast_integer(argv[1]);
            end = cast_integer(argv[2]);
            step = cast_integer(argv[3]);
            break;
        
        default:
            vm_throw(py_type_error);
    }

    this_ = $(argv[0]);
    this_->start = start;
    this_->end = end;
    this_->step = step;
    return $(this_);
}

py_object_t *py_range_len(int argc, py_object_t *argv[])
{
	py_double_t *py_result;
	int len;
	py_range_t *this_;
    assert_argc(argc, 1);
    this_ = $(argv[0]);

    len = (this_->end - this_->start) / this_->step;
    py_result = py_double_new(len);
    return $(py_result);
}

py_object_t *py_range_iterator(int argc, py_object_t *argv[])
{
	py_range_t *this_;
    assert_argc(argc, 1);
    this_ = $(argv[0]);
    this_->cursor = this_->start;
    return $(this_);
}

py_object_t *py_range_next(int argc, py_object_t *argv[])
{
	py_double_t *py_item;
	py_range_t *this_;
    assert_argc(argc, 1);
    this_ = $(argv[0]);

    if (this_->cursor == this_->end)
        vm_throw(py_stop_iteration);
    py_item = py_double_new(this_->cursor);
    this_->cursor += this_->step;
    return $(py_item);
}

native_t py_range_natives[] = {
    {"__next__", py_range_next},
    {"__iter__", py_range_iterator},
    {"__init__", py_range_init},
    {"__len__", py_range_len},
    {NULL}
};

void py_range_class_init()
{
    py_range_class = py_class_new("range");
    py_range_class->py_alloc = py_range_alloc;
    py_class_register_natives(py_range_class, py_range_natives);
}
