#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include "text.h"

// The contents of input string will be destroyed
int split_string(char *string, const char *seperator, char *fields[])
{
    int fields_count = 0;
    char *word, *word_save;
#ifndef _MSC_VER
    word = strtok_r(string, seperator, &word_save);        
#else
	word = strtok_s(string, seperator, &word_save);
#endif
    while (word) {
        fields[fields_count++] = word;
#ifndef _MSC_VER
        word = strtok_r(NULL, seperator, &word_save);
#else
		word = strtok_s(NULL, seperator, &word_save);
#endif
	}
    return fields_count;
}

#define TEXT_CAPACITY 64
void text_init(text_t *this_)
{
    this_->data = (char *)malloc(TEXT_CAPACITY);
    this_->size = 0;
    this_->capacity = TEXT_CAPACITY;
    this_->data[this_->size] = 0;
}

void text_destroy(text_t *this_)
{
    free(this_->data);
}

void text_grow(text_t *this_)
{
    int old_capacity = this_->capacity;
    int new_capacity = old_capacity * 2;

    this_->data = (char *)realloc(this_->data, new_capacity);
    this_->size = this_->size;
    this_->capacity = new_capacity;
}

void text_put_char(text_t *this_, int c)
{
    assert(c != EOF);
    if (this_->size + 1 == this_->capacity)
        text_grow(this_);
    this_->data[this_->size] = c;
    this_->size++;
    this_->data[this_->size] = 0;
}

int text_trim_char(text_t *this_)
{
	char c;
    if (this_->size == 0)
        return 0;
    this_->size--;
    c = this_->data[this_->size];
    this_->data[this_->size] = 0;
    return c;
}

void text_put_buffer(text_t *this_, char *buffer, int length)
{
    while (this_->size + length + 1 > this_->capacity)
        text_grow(this_);

    memcpy(this_->data + this_->size, buffer, length);
    this_->size += length;
    this_->data[this_->size] = 0;

    assert(this_->size + 1 <= this_->capacity);
}

void text_printf(text_t *this_, char *format, ...)
{
	char buffer[256];
    int length;
    va_list ap;
    va_start(ap, format);

    length = vsprintf(buffer, format, ap);
    assert(length < sizeof(buffer));
    text_put_buffer(this_, buffer, length);

    va_end(ap);
}

void text_put_string(text_t *this_, char *string)
{
    int length = strlen(string);
    text_put_buffer(this_, string, length);
}
