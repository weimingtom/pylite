#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "xml_file.h"

xml_file_t *xml_stdout;
xml_file_t *xml_file_new(char *path)
{
	xml_file_t *this_;
	FILE *file;
	if (strcmp(path, "/dev/stdout") == 0)
	{
		file = stdout;
	}
	else
	{
		file = fopen(path, "w");
		if (!file)
			return NULL;
	}
    

    this_ = (xml_file_t *)malloc(sizeof(xml_file_t));
    this_->file = file;
    this_->level = 0;
    return this_;
}

void xml_file_delete(xml_file_t *this_)
{
    fclose(this_->file);
    free(this_);
}

void xml_file_indent(xml_file_t *this_)
{
	int i;
    for (i = 0; i < this_->level; i++)
        fprintf(this_->file, "  ");
}

void xml_file_push(xml_file_t *this_)
{
    this_->level++;
}

void xml_file_pop(xml_file_t *this_)
{
    this_->level--;
}

void xml_file_printf(xml_file_t *this_, char *format, ...)
{
    va_list ap;

    va_start(ap, format);
    vfprintf(this_->file, format, ap);
    va_end(ap);
}

void xml_file_dump(xml_file_t *this_, char *format, ...)
{
    va_list ap;
    
    xml_file_indent(this_);
    va_start(ap, format);
    vfprintf(this_->file, format, ap);
    fprintf(this_->file, "\n");
    va_end(ap);
}
