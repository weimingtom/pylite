#include "root.h"
#include "mod_os.h"
#include "socket.h"
#ifndef _MSC_VER
#include <sys/socket.h>
#endif

py_module_t *py_socket_module;

#define import(type, ...) \
    py_module_import_##type(py_socket_module, __VA_ARGS__)
void py_socket_module_init(void)
{
    py_socket_module = py_module_new(NULL, "socket");
    register_py_module(py_socket_module);

#ifndef _MSC_VER
    import(double, "AF_INET", AF_INET);
    import(double, "SOCK_STREAM", SOCK_STREAM);
    import(double, "SOCK_DGRAM", SOCK_DGRAM);
    import(double, "SOL_SOCKET", SOL_SOCKET);
    import(double, "SO_REUSEADDR", SO_REUSEADDR);
#endif
    import(class, "socket", py_socket_class);
}
