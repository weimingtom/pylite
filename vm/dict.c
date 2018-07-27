#include "root.h"
#include "dict.h"
#include "list_.h"
#include "cast.h"
#include "gc.h"

py_class_t *py_dict_class;

py_dict_t *py_dict_new()
{
    py_dict_t *this_ = py_object_alloc(sizeof(py_dict_t), py_dict_class);
    vector_init(&this_->vector);
    return this_;
}

int py_object_equals(py_object_t *this_, py_object_t *that)
{
    if (this_->py_class == py_double_class) {
        double this_value;
		double that_value;
		if (that->py_class != py_double_class)
            return 0;
        this_value = py_object_to_double(this_);
        that_value = py_object_to_double(that);
        return this_value == that_value;
    }

    if (this_->py_class == py_string_class) {
        char *this_value;
		char *that_value;
		if (that->py_class != py_string_class)
            return 0;
        this_value = ((py_string_t *)this_)->value;
        that_value = ((py_string_t *)that)->value;
        return strcmp(this_value, that_value) == 0;
    }

    assert(0);
    return 0;
}

py_object_t *py_dict_alloc(py_class_t *py_class)
{
    py_dict_t *this_ = py_object_alloc(sizeof(py_dict_t), py_class);
    vector_init(&this_->vector);
    return $(this_);
}

py_object_t *py_dict_init(int argc, py_object_t *argv[])
{
	py_dict_t *this_;
    assert_argc(argc, 1);
    this_ = $(argv[0]);
    return py_none;
}

py_object_t *py_dict_get_item(int argc, py_object_t *argv[])
{
	int i;
	py_object_t *py_index;
	py_dict_t *this_;
    assert_argc(argc, 2);
    this_ = $(argv[0]);
    py_index = argv[1];

    for (i = 0; i < this_->vector.count; i++) {
        py_pair_t *py_pair = this_->vector.data + i;
        if (py_object_equals(py_pair->key, py_index))
            return py_pair->value;
    }
    vm_throw(py_key_error);
}

py_object_t *py_dict_set_item(int argc, py_object_t *argv[])
{
	py_pair_t py_pair;
    int i;
	py_dict_t *this_;
    py_object_t *py_index;
    py_object_t *py_item;
	assert_argc(argc, 3);
    this_ = $(argv[0]);
    py_index = argv[1];
    py_item = argv[2];

    for (i = 0; i < this_->vector.count; i++) {
        py_pair_t *py_pair = this_->vector.data + i;
        if (py_object_equals(py_pair->key, py_index)) {
            py_pair->value = py_item;
            return py_none;
        }
    }

    py_pair.key = py_index;
    py_pair.value = py_item;
    vector_push_back(&this_->vector, py_pair);
    return py_none;
}

py_object_t *py_dict_str(int argc, py_object_t *argv[])
{
	py_string_t *py_result;
	int i;
    py_pair_t *py_pair;
    text_t text;
    py_dict_t *this_;
    assert_argc(argc, 1);
    this_ = $(argv[0]);

    text_init(&text);
    text_put_char(&text, '{');

    vector_each_address (&this_->vector, i, py_pair) {
        py_string_t *py_value;
		py_pair_t *py_pair = this_->vector.data + i;

        // print key
        py_string_t *py_key = py_object_to_string(py_pair->key);
        if (py_key == NULL) {
            text_destroy(&text);
            vm_rethrow();
        }
        text_put_string(&text, py_key->value);

        // print :
        text_put_string(&text, ": ");

        // print value
        py_value = py_object_to_string(py_pair->value);
        if (py_value == NULL) {
            text_destroy(&text);
            vm_rethrow();
        }
        text_put_string(&text, py_value->value);

        if (i != this_->vector.count - 1)
            text_put_string(&text, ", ");
    }

    text_put_char(&text, '}');
    py_result = py_string_new(text.data);
    text_destroy(&text);

    return $(py_result);
}

py_object_t *py_dict_len(int argc, py_object_t *argv[])
{
	py_double_t *py_result;
	py_dict_t *this_;
    assert_argc(argc, 1);
    this_ = $(argv[0]);

    py_result = py_double_new(this_->vector.count);
    return $(py_result);
}

py_object_t *py_dict_items(int argc, py_object_t *argv[])
{
	int i;
    py_pair_t *py_pair;
    py_dict_t *this_;
    py_list_t *py_list;
	assert_argc(argc, 1);
    this_ = $(argv[0]);
    py_list = py_list_new(0);

    vector_each_address (&this_->vector, i, py_pair) {
        py_list_t *py_item = py_list_new(0);
        py_list_push_back(py_item, py_pair->key);
        py_list_push_back(py_item, py_pair->value);
        py_list_push_back(py_list, $(py_item));
    }
    return $(py_list);
}

py_object_t *py_dict_keys(int argc, py_object_t *argv[])
{
	int i;
    py_pair_t *py_pair;
    py_dict_t *this_;
    py_list_t *py_list;
	assert_argc(argc, 1);
    this_ = $(argv[0]);
    py_list = py_list_new(0);

    vector_each_address (&this_->vector, i, py_pair) {
        py_object_t *key = py_pair->key; 
        py_list_push_back(py_list, key);
    }
    return $(py_list);
}

py_object_t *py_dict_values(int argc, py_object_t *argv[])
{
	int i;
    py_pair_t *py_pair;
    py_dict_t *this_;
    py_list_t *py_list;
	assert_argc(argc, 1);
    this_ = $(argv[0]);
    py_list = py_list_new(0);

    vector_each_address (&this_->vector, i, py_pair) {
        py_object_t *value = py_pair->value; 
        py_list_push_back(py_list, value);
    }
    return $(py_list);
}

native_t py_dict_natives[] = {
    {"__init__", py_dict_init},
    {"__getitem__", py_dict_get_item},
    {"__setitem__", py_dict_set_item},
    {"__str__", py_dict_str},
    {"__len__", py_dict_len},
    {"items", py_dict_items},
    {"keys", py_dict_keys},
    {"values", py_dict_values},
    {NULL}
};

void py_dict_mark(py_dict_t *this_)
{
    int i;
    py_pair_t *py_pair;
    vector_each_address (&this_->vector, i, py_pair) {
        gc_mark(py_pair->key);
        gc_mark(py_pair->value);
    }
}

void py_dict_free(py_dict_t *this_)
{
    vector_destroy(&this_->vector);
}    

void py_dict_class_init(void)
{
    py_dict_class = py_class_new("dict");
    py_dict_class->py_alloc = py_dict_alloc;
    py_dict_class->gc_mark = $(py_dict_mark);
    py_dict_class->gc_free = $(py_dict_free);
    py_class_register_natives(py_dict_class, py_dict_natives);
}
