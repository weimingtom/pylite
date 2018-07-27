#include "root.h"
#include "socket.h"
#include "tuple.h"
#include "file.h"
#include "cast.h"
#ifndef _MSC_VER
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include <netdb.h>
#else
#include <winsock2.h>
#endif

py_class_t *py_socket_class;

py_object_t *py_socket_alloc()
{
    py_socket_t *this_ = py_object_alloc(sizeof(py_socket_t), py_socket_class);
    this_->family = -1;
    this_->fd = -1;
    return $(this_);
}

py_object_t *py_socket_init(int argc, py_object_t *argv[])
{
    int family;
    int type;
    int proto;
    int fd;
	py_socket_t *this_;
    assert_argc(argc, 4);
    this_ = $(argv[0]);
    family = cast_integer(argv[1]);
    type = cast_integer(argv[2]);
    proto = cast_integer(argv[3]);

    fd = socket(family, type, proto);
    if (fd < 0)
        vm_throw(py_io_error);
    this_->fd = fd;
    this_->family = family;

    return py_none;
}

py_object_t *py_socket_new(int fd, int family)
{
    py_socket_t *this_ = py_object_alloc(sizeof(py_socket_t), py_socket_class);
    this_->family = family;
    this_->fd = fd;
    return $(this_);
}

static py_object_t *to_address(py_tuple_t *py_tuple, struct sockaddr_in *sin)
{
#ifndef _MSC_VER
    if (py_tuple->vector.count != 2) 
        vm_throw(py_type_error);

    py_object_t *py_host = vector_get(&py_tuple->vector, 0);
    py_object_t *py_port = vector_get(&py_tuple->vector, 1);
    char *host = cast_string(py_host);
    int port = cast_integer(py_port);

    struct hostent *entry = gethostbyname(host);
    if (entry == NULL)
        vm_throw(py_type_error);
    in_addr_t *in_addr = (in_addr_t *) entry->h_addr_list[0];

    sin->sin_family = AF_INET;
    sin->sin_addr.s_addr = *in_addr;
    sin->sin_port = htons(port);

    return py_none;
#else
	vm_throw(py_type_error);
#endif
}

py_object_t *py_socket_bind(int argc, py_object_t *argv[])
{
	int error;
	struct sockaddr_in sin;
    py_tuple_t *py_tuple;
	py_socket_t *this_;
    assert_argc(argc, 2);
    this_ = $(argv[0]);
	py_tuple = cast_object_tuple(argv[1]);

    if (to_address(py_tuple, &sin) == NULL)
        vm_rethrow();

    error = bind(this_->fd, $(&sin), sizeof(sin));
    if (error < 0)
        vm_throw(py_io_error);
    return py_none;
}

py_object_t *py_socket_connect(int argc, py_object_t *argv[])
{
	int error;
    py_socket_t *this_;
	py_tuple_t *py_tuple;
    struct sockaddr_in sin;
    assert_argc(argc, 2);
    this_ = $(argv[0]);
	py_tuple = cast_object_tuple(argv[1]);

    if (to_address(py_tuple, &sin) == NULL)
        vm_rethrow();

    error = connect(this_->fd, $(&sin), sizeof(sin));
    if (error < 0)
        vm_throw(py_io_error);
    return py_none;
}

py_object_t *py_socket_listen(int argc, py_object_t *argv[])
{
	int backlog;
	py_socket_t *this_;
    assert_argc(argc, 2);
    this_ = $(argv[0]);
    backlog = cast_integer(argv[1]);

    listen(this_->fd, backlog);
    return py_none;
}

py_object_t *py_socket_accept(int argc, py_object_t *argv[])
{
	int client_fd;
    py_object_t *py_client;
    py_object_t *py_client_addr;
    py_tuple_t *py_tuple;
	struct sockaddr_in client_addr;
	py_socket_t *this_;
	int client_addr_size;
    assert_argc(argc, 1);
	this_ = cast_object_socket(argv[0]);

    client_addr_size = sizeof(client_addr);
    client_fd = accept(this_->fd, $(&client_addr), &client_addr_size);
    if (client_fd < 0)
        vm_throw(py_io_error);

    py_client = $(py_socket_new(client_fd, this_->family));
    py_client_addr = py_none; // Ignore the address

    py_tuple = py_tuple_new();
    py_tuple_append(py_tuple, py_client);
    py_tuple_append(py_tuple, py_client_addr); 
    return $(py_tuple);
}

py_object_t *py_socket_setsockopt(int argc, py_object_t *argv[])
{
	int level;
    int name;
    int value;
	py_socket_t *this_;
	int error;
	int len;
    assert_argc(argc, 4);
    this_ = $(argv[0]);
    level = cast_integer(argv[1]);
    name = cast_integer(argv[2]);
    value = cast_integer(argv[3]);

    len = sizeof(value);
    error = setsockopt(this_->fd, level, name, (const char*)&value, len);
    if (error < 0)
        vm_throw(py_io_error);
    return py_none;
}

py_object_t *py_socket_getsockopt(int argc, py_object_t *argv[])
{
	py_socket_t *this_;
    assert_argc(argc, 2);
    this_ = $(argv[0]);
    return py_none;
}

py_object_t *py_socket_send(int argc, py_object_t *argv[])
{
#ifndef _MSC_VER
    assert_argc(argc, 2);
    py_socket_t *this = $(argv[0]);

    char *buffer = cast_string(argv[1]);
    int count = strlen(buffer);
    int error = write(this_->fd, buffer, count);
    if (error < 0)
        vm_throw(py_io_error);

    return py_none;
#else
	vm_throw(py_io_error);
#endif
}

py_object_t *py_socket_recv(int argc, py_object_t *argv[])
{
#ifndef _MSC_VER
    assert_argc(argc, 2);
    py_socket_t *this = $(argv[0]);
    int count = cast_integer(argv[1]);

    char *buffer = malloc(count * sizeof(char *));
    int error = read(this_->fd, buffer, count);
	if (error < 0) {
		free(buffer);
		vm_throw(py_io_error);
	}
    buffer[error] = 0; 

    py_string_t *py_string = py_string_new(buffer);
	free(buffer);
    return $(py_string);
#else
	vm_throw(py_io_error);
#endif
}

py_object_t *py_socket_close(int argc, py_object_t *argv[])
{
#ifndef _MSC_VER
    assert_argc(argc, 1);
    py_socket_t *this = $(argv[0]);
    close(this_->fd);
    return py_none;
#else
	vm_throw(py_io_error);
#endif
}

py_object_t *py_socket_makefile(int argc, py_object_t *argv[])
{
	py_file_t *py_file;
	char *mode;
	py_socket_t *this_;
    assert_argc(argc, 2);
    this_ = $(argv[0]);
    mode = cast_string(argv[1]);

    py_file = py_file_fdopen(this_->fd, mode);
    if (py_file == NULL)
        vm_rethrow();
    return $(py_file);
}

native_t py_socket_natives[] = {
    {"__init__", py_socket_init},
    {"accept", py_socket_accept},
    {"send", py_socket_send},
    {"recv", py_socket_recv},
    {"close", py_socket_close},
    {"makefile", py_socket_makefile},
    {"bind", py_socket_bind},
    {"listen", py_socket_listen},
    {"connect", py_socket_connect},
    {"setsockopt", py_socket_setsockopt},
    {"getsockopt", py_socket_getsockopt},
    {NULL}
};

void py_socket_class_init()
{
    py_socket_class = py_class_new("socket");
    py_socket_class->py_alloc = py_socket_alloc;
    py_class_register_natives(py_socket_class, py_socket_natives);
}
