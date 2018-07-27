#include "root.h"
#include "tuple.h"
#include "slice.h"
#include "cast.h"
#include "gc.h"

py_class_t *py_tuple_class;

py_tuple_t *py_tuple_new()
{
    py_tuple_t *this_ = py_object_alloc(sizeof(py_tuple_t), py_tuple_class);
    vector_init(&this_->vector);
    this_->cursor = 0;
    return this_;
}

void py_tuple_append(py_tuple_t *this_, py_object_t *py_item)
{
    vector_push_back(&this_->vector, py_item);
}

py_object_t *py_tuple_get_single(py_tuple_t *this_, py_object_t *py_index)
{
    int index = cast_integer(py_index);
    py_object_t *py_item = vector_get(&this_->vector, index);
    return py_item;
}

py_object_t *py_tuple_get_slice(py_tuple_t *this_, py_object_t *py_index)
{
	py_tuple_t *that;
	int i;
    py_slice_t *py_slice = $(py_index);
    int count = this_->vector.count;
    int start;
    int stop;
    if (py_slice_parse(py_slice, &start, &stop, count) != NULL)
        vm_rethrow();

    that = py_tuple_new();
    for (i = start; i < stop; i++) {
        py_object_t *py_item = vector_get(&this_->vector, i);
        py_tuple_append(that, py_item);
    }
    return $(that);
}

py_object_t *py_tuple_get_item(int argc, py_object_t *argv[])
{
    py_tuple_t *this_ = $(argv[0]);
    py_object_t *py_index = argv[1];

    if (py_index->py_class == py_double_class)
        return py_tuple_get_single(this_, py_index);

    if (py_index->py_class == py_slice_class)
        return py_tuple_get_slice(this_, py_index);

    vm_throw(py_type_error);
}

py_object_t *py_tuple_str(int argc, py_object_t *argv[])
{
	py_string_t *py_result;
	int i;
    py_object_t *py_item;
    text_t text;
    py_tuple_t *this_;
    assert_argc(argc, 1);
    this_ = $(argv[0]);

    text_init(&text);
    text_put_char(&text, '(');

    vector_each (&this_->vector, i, py_item) {
        py_string_t *py_string = py_object_to_string(py_item);
        if (py_string == NULL) {
            text_destroy(&text);
            vm_rethrow();
        }

        text_put_string(&text, py_string->value);
        if (i != this_->vector.count - 1)
            text_put_string(&text, ", ");
    }

    text_put_char(&text, ')');
    py_result = py_string_new(text.data);
    text_destroy(&text);

    return $(py_result);
}

py_object_t *py_tuple_len(int argc, py_object_t *argv[])
{
	py_double_t *py_result;
	py_tuple_t *this_;
    assert_argc(argc, 1);
    this_ = $(argv[0]);

    py_result = py_double_new(this_->vector.count);
    return $(py_result);
}

py_object_t *py_tuple_iterator(int argc, py_object_t *argv[])
{
	py_tuple_t *this_;
    assert_argc(argc, 1);
    this_ = $(argv[0]);
    this_->cursor = 0;
    return $(this_);
}

py_object_t *py_tuple_next(int argc, py_object_t *argv[])
{
	py_object_t *py_item;
	py_tuple_t *this_;
    assert_argc(argc, 1);
    this_ = $(argv[0]);

    if (this_->cursor == this_->vector.count)
        vm_throw(py_stop_iteration);
    py_item = vector_get(&this_->vector, this_->cursor);
    this_->cursor++;
    return py_item;
}

native_t py_tuple_natives[] = {
    {"__getitem__", py_tuple_get_item},
    {"__iter__", py_tuple_iterator},
    {"__next__", py_tuple_next},
    {"__str__", py_tuple_str},
    {"__len__", py_tuple_len},
    {NULL}
};

void py_tuple_mark(py_tuple_t *this_)
{
    int i;
    py_object_t *py_item;
    vector_each (&this_->vector, i, py_item)
        gc_mark(py_item);
}

void py_tuple_free(py_tuple_t *this_)
{
    vector_destroy(&this_->vector);
}    

void py_tuple_class_init(void)
{
    py_tuple_class = py_class_new("tuple");
    py_tuple_class->gc_mark = $(py_tuple_mark);
    py_tuple_class->gc_free = $(py_tuple_free);
    py_class_register_natives(py_tuple_class, py_tuple_natives);
}
