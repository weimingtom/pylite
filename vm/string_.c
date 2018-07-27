#include "root.h"
#include "string_.h"
#include "tuple.h"
#include "slice.h"
#include "list_.h"
#include "cast.h"

py_class_t *py_string_class;

py_string_t *py_string_new(char *value)
{
    py_string_t *this_ = py_object_alloc(sizeof(py_string_t), py_string_class);
    this_->value = strdup(value);
    return this_;
}

py_object_t *py_string_islower(int argc, py_object_t *argv[])
{
	char *p;
	py_string_t *this_;
    assert_argc(argc, 1);
    this_ = $(argv[0]);

    for (p = this_->value; *p; p++) {
        if (!islower((int)*p))
            return py_false;
    }
    return py_true;
}

py_object_t *py_string_isupper(int argc, py_object_t *argv[])
{
	char *p;
	py_string_t *this_;
    assert_argc(argc, 1);
    this_ = $(argv[0]);

    for (p = this_->value; *p; p++) {
        if (!islower((int)*p))
            return py_false;
    }
    return py_true;
}

py_object_t *py_string_lower(int argc, py_object_t *argv[])
{
	py_string_t *that;
	char *p;
	py_string_t *this_;
	assert_argc(argc, 1);
    this_ = $(argv[0]);

    that = py_string_new(this_->value); 
    for (p = that->value; *p; p++)
        *p = tolower((int)*p);
    return $(that);
}

py_object_t *py_string_upper(int argc, py_object_t *argv[])
{
	py_string_t *that;
	char *p;
	py_string_t *this_;
    assert_argc(argc, 1);
    this_ = $(argv[0]);

    that = py_string_new(this_->value); 
    for (p = that->value; *p; p++)
        *p = toupper((int)*p);
    return $(that);
}

py_object_t *py_string_add(int argc, py_object_t *argv[])
{
	py_string_t *target;
	char *buf;
	int that_size;
	int this_size;
	py_string_t *that;
	py_string_t *this_;
    assert_argc(argc, 2);
    this_ = cast_object_string(argv[0]);
    that = cast_object_string(argv[1]);

    this_size = strlen(this_->value);
    that_size = strlen(that->value);
    buf = (char *)malloc((this_size + that_size + 1) * sizeof(char));
    strcpy(buf, this_->value);
    strcat(buf, that->value);
    target = py_string_new(buf);
	free(buf);
    return $(target);
}

py_object_t *py_string_len(int argc, py_object_t *argv[])
{
	py_double_t *py_result;
	int len;
	py_string_t *this_;
    assert_argc(argc, 1);
    this_ = $(argv[0]);

    len = strlen(this_->value);
    py_result = py_double_new(len);
    return $(py_result);
}

py_object_t *py_string_str(int argc, py_object_t *argv[])
{
	py_string_t *this_;
    assert_argc(argc, 1);
    this_ = $(argv[0]);
    return $(this_);
}

py_string_t *arg_to_string(py_object_t *args, int index)
{
    py_object_t *arg;
    if (args->py_class == py_tuple_class) {
        py_tuple_t *py_tuple = $(args);
        if (index < 0 || index >= py_tuple->vector.count)
            vm_throw(py_index_error);
        arg = vector_get(&py_tuple->vector, index);
    } else {
        arg = args;
    }

    return py_object_to_string(arg);
}

py_object_t *py_string_eq(int argc, py_object_t *argv[])
{
    py_string_t *this_ = cast_object_string(argv[0]);
    py_string_t *that = cast_object_string(argv[1]);

    if (strcmp(this_->value, that->value) == 0)
        return py_true;
    else
        return py_false;
}

py_object_t *py_string_ne(int argc, py_object_t *argv[])
{
    py_string_t *this_ = cast_object_string(argv[0]);
	py_string_t *that = cast_object_string(argv[1]);

    if (strcmp(this_->value, that->value) != 0)
        return py_true;
    else
        return py_false;
}

py_object_t *py_string_mod(int argc, py_object_t *argv[])
{
	char *p;
	py_string_t *that;
	int index = 0;
    text_t text;
    py_object_t *args;
	py_string_t *this_;
    assert_argc(argc, 2);
    this_ = $(argv[0]);
    args = argv[1];
 
    text_init(&text);
    for (p = this_->value; *p; p++) {
        py_string_t *py_string;
		char c = *p;
        if (c != '%') {
            text_put_char(&text, c);
            continue;
        }

        p++;
        c = *p;
        if (c == '%') {
            text_put_char(&text, c);
            continue;
        }

        if (!(c == 's' || c == 'd' || c == 'f')) {
            text_destroy(&text);
            vm_throw(py_type_error);
        }

        py_string = arg_to_string(args, index);
        if (py_string == NULL)
            vm_rethrow();
        index++;
        text_put_string(&text, py_string->value);
    }
    that = py_string_new(text.data);
    text_destroy(&text);

    return $(that);
}

py_object_t *py_string_join(int argc, py_object_t *argv[])
{
	py_string_t *py_result;
	int last;
	int i;
    py_object_t *py_item;
    text_t text;
    py_list_t *py_list;
	py_string_t *this_;
    assert_argc(argc, 2);
	this_ = $(argv[0]);
    py_list = cast_object_list(argv[1]);

    text_init(&text);

    last = py_list->vector.count - 1;
    vector_each(&py_list->vector, i, py_item) {
        if (py_item->py_class != py_string_class) {
            text_destroy(&text);
            vm_throw(py_type_error);
        }

        text_put_string(&text, ((py_string_t *)py_item)->value);
        if (i != last)
            text_put_string(&text, this_->value);
    }

    py_result = py_string_new(text.data);
    text_destroy(&text);
    return $(py_result);
}

py_object_t *py_string_get_single(py_string_t *this_, py_object_t *py_index)
{
	py_string_t *that;
    char buffer[2];
    int index = cast_integer(py_index);
    int len = strlen(this_->value);
    if (index < 0 || index >= len)
        vm_throw(py_index_error);

    buffer[0] = this_->value[index];
    buffer[1] = 0;
    that = py_string_new(buffer);
    return $(that);
}

py_object_t *py_string_get_slice(py_string_t *this_, py_object_t *py_index)
{
	py_string_t *that;
	char *buffer;
    py_slice_t *py_slice = $(py_index);
    int start;
    int stop;
    int len = strlen(this_->value);
    if (py_slice_parse(py_slice, &start, &stop, len) != NULL)
        vm_rethrow();

    buffer = (char *)malloc((stop - start + 1) * sizeof(char));
    memcpy(buffer, this_->value + start, stop - start);
    buffer[stop - start] = 0;
    that = py_string_new(buffer);
	free(buffer);
	return $(that);
}

py_object_t *py_string_get_item(int argc, py_object_t *argv[])
{
	py_object_t *py_index;
	py_string_t *this_;
    assert_argc(argc, 2);
    this_ = $(argv[0]);
    py_index = argv[1];

    if (py_index->py_class == py_double_class)
        return py_string_get_single(this_, py_index);

    if (py_index->py_class == py_slice_class)
        return py_string_get_slice(this_, py_index);

    vm_throw(py_type_error);
}

py_object_t *py_string_split(int argc, py_object_t *argv[])
{
	char *token;
	py_list_t *py_list;
	char *buffer;
	int length;
	char *delimit;
    py_string_t *this_;
	assert_argc(argc, 2);
    this_ = $(argv[0]);
    delimit = cast_string(argv[1]);

    length = strlen(this_->value); 
    buffer = (char *)malloc(length * sizeof(char));
    strcpy(buffer, this_->value);

    py_list = py_list_new(0);
    token = strtok(buffer, delimit);
    while (token != NULL) {
        py_string_t *py_item = py_string_new(token);
        py_list_push_back(py_list, $(py_item));
        token = strtok(NULL, delimit);
    }
	free(buffer);
    return $(py_list);
}

py_object_t *py_string_find(int argc, py_object_t *argv[])
{
	py_double_t *py_index;
	char *substr;
	int index;
    char *haystack;
	char *needle;
	py_string_t *this_;
    assert_argc(argc, 2);
    this_ = $(argv[0]);
    needle = cast_string(argv[1]);
    haystack = this_->value;

    substr = strstr(haystack, needle);
    if (substr == NULL)
        index = -1;
    else
        index = substr - haystack;
    py_index = py_double_new(index);

    return $(py_index);
}

native_t py_string_natives[] = {
    {"__add__", py_string_add},
    {"__str__", py_string_str},
    {"__eq__", py_string_eq},
    {"__ne__", py_string_ne},
    {"__mod__", py_string_mod},
    {"__len__", py_string_len},
    {"__getitem__", py_string_get_item},
    {"find", py_string_find},
    {"split", py_string_split},
    {"join", py_string_join},
    {"islower", py_string_islower},
    {"isupper", py_string_isupper},
    {"lower", py_string_lower},
    {"upper", py_string_upper},
    {NULL}
};

void py_string_free(py_string_t *this_)
{
    free(this_->value);
}    

void py_string_class_init(void)
{
    py_string_class = py_class_new("string");
    py_string_class->gc_free = $(py_string_free);
    py_class_register_natives(py_string_class, py_string_natives);
}
