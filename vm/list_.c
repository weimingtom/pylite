#include "root.h"
#include "list_.h"
#include "slice.h"
#include "cast.h"
#include "gc.h"

py_class_t *py_list_class;

py_list_t *py_list_new(int count)
{
	int i;
    py_list_t *this_ = py_object_alloc(sizeof(py_list_t), py_list_class);
    vector_init(&this_->vector);
    this_->cursor = 0;
    for (i = 0; i < count; i++)
        vector_push_back(&this_->vector, py_none);
    return this_;
}

void py_list_push_back(py_list_t *this_, py_object_t *py_item)
{
    vector_push_back(&this_->vector, py_item);
}

py_object_t *py_list_alloc(py_class_t *py_class)
{
    py_list_t *this_ = py_object_alloc(sizeof(py_list_t), py_class);
    vector_init(&this_->vector);
    this_->cursor = 0;
    return $(this_);
}

py_object_t *py_list_init(int argc, py_object_t *argv[])
{
	py_list_t *this_;
    assert_argc(argc, 1);
    this_ = $(argv[0]);
    return py_none;
}

py_object_t *py_list_append(int argc, py_object_t *argv[])
{
	py_object_t *py_item;
	py_list_t *this_;
    assert_argc(argc, 2);
    this_ = $(argv[0]);
    py_item = argv[1];
    py_list_push_back(this_, py_item);
    return py_none;
}

// insert item before index
py_object_t *py_list_insert(int argc, py_object_t *argv[])
{
	py_object_t **vector;
	py_object_t *py_item;
	int index;
	py_list_t *this_;
	int i;
    assert_argc(argc, 3);
    this_ = $(argv[0]);
    index = cast_range(argv[1], 0, this_->vector.count);
    py_item = argv[2];

    vector_push_back(&this_->vector, py_none);
    vector = this_->vector.data;
    for (i = this_->vector.count - 1; i > index; i--)
        vector[i] = vector[i - 1];
    vector[index] = py_item;
    return py_none;
}

py_object_t *py_list_get_single(py_list_t *this_, py_object_t *py_index)
{
    int index = cast_range(py_index, 0, this_->vector.count);
    py_object_t *py_item = vector_get(&this_->vector, index);
    return py_item;
}

py_object_t *py_list_get_slice(py_list_t *this_, py_object_t *py_index)
{
	py_list_t *that;
	int i;
    py_slice_t *py_slice = $(py_index);
    int count = this_->vector.count;
    int start;
    int stop;
    if (py_slice_parse(py_slice, &start, &stop, count) != NULL)
        vm_rethrow();

    that = py_list_new(stop - start);
    for (i = start; i < stop; i++) {
        int j = i - start; 
        that->vector.data[j] = this_->vector.data[i];
    }
    return $(that);
}

py_object_t *py_list_get_item(int argc, py_object_t *argv[])
{
	py_object_t *py_index;
	py_list_t *this_;
    assert_argc(argc, 2);
    this_ = $(argv[0]);
    py_index = argv[1];

    if (py_index->py_class == py_double_class)
        return py_list_get_single(this_, py_index);

    if (py_index->py_class == py_slice_class)
        return py_list_get_slice(this_, py_index);

    vm_throw(py_type_error);
}

py_object_t *py_list_set_item(int argc, py_object_t *argv[])
{
	py_object_t *py_item;
	int index;
	py_list_t *this_;
    assert_argc(argc, 3);
    this_ = $(argv[0]);
    index = cast_range(argv[1], 0, this_->vector.count);
    py_item = argv[2];

    vector_set(&this_->vector, index, py_item);
    return py_none;
}

py_object_t *py_list_str(int argc, py_object_t *argv[])
{
	py_string_t *py_result;
	int i;
    py_object_t *py_item;
    py_list_t *this_;
    text_t text;
    assert_argc(argc, 1);
    this_ = $(argv[0]);

    text_init(&text);
    text_put_char(&text, '[');

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

    text_put_char(&text, ']');
    py_result = py_string_new(text.data);
    text_destroy(&text);

    return $(py_result);
}

py_object_t *py_list_len(int argc, py_object_t *argv[])
{
	py_double_t *py_result;
	py_list_t *this_;
    assert_argc(argc, 1);
    this_ = $(argv[0]);

    py_result = py_double_new(this_->vector.count);
    return $(py_result);
}

py_object_t *py_list_iterator(int argc, py_object_t *argv[])
{
	py_list_t *this_;
    assert_argc(argc, 1);
    this_ = $(argv[0]);
    this_->cursor = 0;
    return $(this_);
}

py_object_t *py_list_next(int argc, py_object_t *argv[])
{
	py_object_t *py_item;
	py_list_t *this_;
    assert_argc(argc, 1);
    this_ = $(argv[0]);

    if (this_->cursor == this_->vector.count)
        vm_throw(py_stop_iteration);
    py_item = vector_get(&this_->vector, this_->cursor);
    this_->cursor++;
    return py_item;
}

native_t py_list_natives[] = {
    {"append", py_list_append},
    {"insert", py_list_insert},
    {"__init__", py_list_init},
    {"__iter__", py_list_iterator},
    {"__next__", py_list_next},
    {"__getitem__", py_list_get_item},
    {"__setitem__", py_list_set_item},
    {"__str__", py_list_str},
    {"__len__", py_list_len},
    {NULL}
};

void py_list_mark(py_list_t *this_)
{
    int i;
    py_object_t *py_item;
    vector_each (&this_->vector, i, py_item)
        gc_mark(py_item);
}

void py_list_free(py_list_t *this_)
{
    vector_destroy(&this_->vector);
}    

void py_list_class_init(void)
{
    py_list_class = py_class_new("list");
    py_list_class->py_alloc = py_list_alloc;
    py_list_class->gc_mark = $(py_list_mark);
    py_list_class->gc_free = $(py_list_free);
    py_class_register_natives(py_list_class, py_list_natives);
}
