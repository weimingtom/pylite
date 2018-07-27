#ifndef _VM_CAST_H
#define _VM_CAST_H

#include "object.h"
#include "class.h"

#include "double.h"
#include "string_.h"
#include "none.h"
#include "bool.h"

#include "error.h"
#include "vm.h"
#include "native.h"
#include "list_.h"
#include "tuple.h"
#include "socket.h"

#if 0
#define cast_double(py_object)                          \
    ({                                                  \
        if (py_object->py_class != py_double_class)     \
            vm_throw(py_type_error);                    \
        py_double_t *py_double = $(py_object);          \
        double value = py_double->value;                \
        value;                                          \
    })
#else
static __inline double cast_double(py_object_t *py_object)
{
	double value;
	py_double_t *py_double;
	if (py_object->py_class != py_double_class)
		vm_throw_double(py_type_error);
	py_double = $(py_object);
	value = py_double->value;
	return value;
}
#endif

#if 0
#define cast_integer(py_object)                         \
    ({                                                  \
        if (py_object->py_class != py_double_class)     \
            vm_throw(py_type_error);                    \
        py_double_t *py_double = $(py_object);          \
        int value = (int) py_double->value;             \
        value;                                          \
    })
#else
static __inline int cast_integer(py_object_t *py_object)
{
	int value;
	py_double_t *py_double;
	if (py_object->py_class != py_double_class)
		vm_throw_double(py_type_error);
	py_double = $(py_object);
	value = (int)py_double->value;
	return value;
}
#endif

#if 0
#define cast_range(py_object, start, end)               \
    ({                                                  \
        if (py_object->py_class != py_double_class)     \
            vm_throw(py_type_error);                    \
        py_double_t *py_double = $(py_object);          \
        int value = (int) py_double->value;             \
        if (!(start <= value && value < end))           \
            vm_throw(py_index_error);                   \
        value;                                          \
    })
#else
static __inline int cast_range(py_object_t *py_object, int start, int end)
{
	int value;
	py_double_t *py_double;
	if (py_object->py_class != py_double_class) 
		vm_throw_double(py_type_error);
	py_double = $(py_object);
	value = (int)py_double->value;
	if (!(start <= value && value < end))
		vm_throw_double(py_index_error);
	return value;
}
#endif

#if 0
#define cast_string(py_object)                          \
    ({                                                  \
        if (py_object->py_class != py_string_class)     \
            vm_throw(py_type_error);                    \
        py_string_t *py_string = $(py_object);          \
        char *value = py_string->value;                 \
        value;                                          \
    })
#else
static __inline char *cast_string(py_object_t *py_object)
{
	char *value;
	py_string_t *py_string;
	if (py_object->py_class != py_string_class)   
		vm_throw(py_type_error);                  
	py_string = $(py_object);        
	value = py_string->value;               
	return value;
}
#endif

#if 0
#define cast_object(py_object, kind)                    \
    ({                                                  \
        if (py_object->py_class != py_##kind##_class)   \
            vm_throw(py_type_error);                    \
        (py_##kind##_t *) py_object;                    \
    })
#else
static __inline py_string_t *cast_object_string(py_object_t *py_object)
{
	if (py_object->py_class != py_string_class)
		vm_throw(py_type_error); 
	return (py_string_t *) py_object; 
}
static __inline py_list_t *cast_object_list(py_object_t *py_object)
{
	if (py_object->py_class != py_list_class)
		vm_throw(py_type_error);
	return (py_list_t *)py_object;
}
static __inline py_tuple_t *cast_object_tuple(py_object_t *py_object)
{
	if (py_object->py_class != py_tuple_class)
		vm_throw(py_type_error);
	return (py_tuple_t *)py_object;
}
static __inline py_socket_t *cast_object_socket(py_object_t *py_object)
{
	if (py_object->py_class != py_socket_class)
		vm_throw(py_type_error);
	return (py_socket_t *)py_object;
}
#endif

#define assert_argc(argc, count)                        \
    do {                                                \
        if (argc != count)                              \
            vm_throw(py_type_error);                    \
    } while (0)

#endif
