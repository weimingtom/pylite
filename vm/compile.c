//#include <libgen.h>
#include "root.h"
#include "compile.h"

static int succeed(int status)
{
#if !defined(_MSC_VER)
    return (status != -1) && WIFEXITED(status) && (WEXITSTATUS(status) == 0);
#else
	return (status != -1);
#endif
}

void check_compiler(void)
{
#ifndef _MSC_VER
	int status = system("which pycom >/dev/null");
    if (!succeed(status)) {
        fprintf(stderr, "The compiler 'pycom' is not found in PATH environment!\n");
        exit(EXIT_FAILURE);
    }
#endif
}

void compile_python(char *py_path, char *xml_path)
{
	int status;
    char command[256];

#ifndef _MSC_VER
    sprintf(command, "pycom %s -o %s", py_path, xml_path);
#else
	sprintf(command, "..\\Debug\\pycom.exe %s -o %s", py_path, xml_path);
#endif
    status = system(command);
    if (!succeed(status)) {
        fprintf(stderr, "Execute compiler('%s') failed!\n", command);
        exit(EXIT_FAILURE);
    }
}
