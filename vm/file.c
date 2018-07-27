#include "root.h"
#include "file.h"
#include "cast.h"

py_class_t *py_file_class;

py_file_t *py_file_fopen(char *path, char *mode)
{
	py_file_t *this_;
    FILE *file = fopen(path, mode);
    if (file == NULL)
        vm_throw(py_io_error);
    this_ = py_object_alloc(sizeof(py_file_t), py_file_class);
    this_->file = file;
    return this_;
}

py_file_t *py_file_fdopen(int fd, char *mode)
{
	py_file_t *this_;
    FILE *file = fdopen(fd, mode);
    if (file == NULL)
        vm_throw(py_io_error);
    this_ = py_object_alloc(sizeof(py_file_t), py_file_class);
    this_->file = file;
    return this_;
}

py_object_t *py_file_read(int argc, py_object_t *argv[])
{
	py_string_t *py_string;
	char *buffer;
	int count;
	py_file_t *this_;
    assert_argc(argc, 2);
    this_ = $(argv[0]);
    count = cast_integer(argv[1]);

    buffer = (char *)malloc(count * sizeof(char));
    count = fread(buffer, 1, count, this_->file);
    buffer[count] = 0;

    py_string = py_string_new(buffer);
	free(buffer);
    return $(py_string);
}

py_object_t *py_file_write(int argc, py_object_t *argv[])
{
	char *string;
	py_file_t *this_;
    assert_argc(argc, 2);
    this_ = $(argv[0]);
    string = cast_string(argv[1]);

    fputs(string, this_->file); 
    return py_none;
}

py_object_t *py_file_readline(int argc, py_object_t *argv[])
{
	py_string_t *py_string;
	char *line;
	py_file_t *this_;
    char buffer[1024];
    assert_argc(argc, 1);
    this_ = $(argv[0]);

    line = fgets(buffer, sizeof(buffer), this_->file);
    if (line == NULL)
        vm_throw(py_io_error);

    py_string = py_string_new(line);
    return $(py_string);
}

py_object_t *py_file_flush(int argc, py_object_t *argv[])
{
	py_file_t *this_;
    assert_argc(argc, 1);
    this_ = $(argv[0]);
    fflush(this_->file);
    return py_none;
}

py_object_t *py_file_close(int argc, py_object_t *argv[])
{
	py_file_t *this_;
    assert(argc == 1);
    this_ = $(argv[0]);
    fclose(this_->file);
    return py_none;
}

py_object_t *py_file_iterator(int argc, py_object_t *argv[])
{
	py_file_t *this_;
    assert_argc(argc, 1);
    this_ = $(argv[0]);
    return $(this_);
}

py_object_t *py_file_next(int argc, py_object_t *argv[])
{
	py_string_t *py_line;
	char *line;
	char buffer[1024];
    py_file_t *this_;
    assert_argc(argc, 1);
    this_ = $(argv[0]);

    line = fgets(buffer, sizeof(buffer), this_->file);
    if (line == NULL)
        vm_throw(py_stop_iteration);
    py_line = py_string_new(line);
    return $(py_line);
}

native_t py_file_natives[] = {
    {"read", py_file_read},
    {"write", py_file_write},
    {"readline", py_file_readline},
    {"flush", py_file_flush},
    {"close", py_file_close},
    {"__iter__", py_file_iterator},
    {"__next__", py_file_next},
    {NULL}
};

void py_file_class_init()
{
    py_file_class = py_class_new("file");
    py_class_register_natives(py_file_class, py_file_natives);
}
