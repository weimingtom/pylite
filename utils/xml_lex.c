#include <assert.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "text.h"
#include "xml_lex.h"

#define isblank_(c) ((c) == ' ' || (c) == '\t')

xml_token_t *xml_token_new(int type, char *value)
{
    xml_token_t *this_ = (xml_token_t *)malloc(sizeof(xml_token_t));
    this_->type = type;
    switch (type) {
        case XML_TOKEN_NEWLINE:
        case XML_TOKEN_STRING:
        case XML_TOKEN_SYMBOL:
            this_->svalue = strdup(value);
            break;

        case XML_TOKEN_DOUBLE:
            this_->dvalue = strtod(value, NULL);
            break;

        case XML_TOKEN_PUSH:
        case XML_TOKEN_POP:
            this_->svalue = NULL;
            break;

        default:
            assert(0);
    }
    return this_;
}

void xml_token_dump(xml_token_t *this_)
{
    switch (this_->type) {
        case XML_TOKEN_DOUBLE:
            printf("DOUBLE  %lf\n", this_->dvalue);
            break;

        case XML_TOKEN_STRING:
            printf("STRING  \"%s\"\n", this_->svalue);
            break;

        case XML_TOKEN_SYMBOL:
            printf("SYMBOL  \"%s\"\n", this_->svalue);
            break;

        case XML_TOKEN_PUSH:
            puts("PUSH  {");
            break;

        case XML_TOKEN_POP:
            puts("POP  }");
            break;

        case XML_TOKEN_NEWLINE:
            puts("NEWLINE");
            break;

        default:
            assert(0);
    }
}

void xml_lex_error(xml_lex_t *this_, char *format, ...)
{
	va_list ap;
    fprintf(stderr, "%s:%d: error: ", this_->file_name, this_->line_number);

    va_start(ap, format);
    vfprintf(stderr, format, ap);
    va_end(ap);

    exit(EXIT_FAILURE);
}

xml_lex_t *xml_lex_new(char *file_name)
{
    xml_lex_t *this_ = (xml_lex_t *)malloc(sizeof(xml_lex_t));
    FILE *file = fopen(file_name, "r");
    if (!file)
        return NULL;

    this_->file = file;
    this_->file_name = file_name;
    this_->line_number = 1;

    this_->last_tabs = 0;
    this_->tab_length = 2;
    stack_init(&this_->token_stack);
    return this_;
}

int xml_lex_get_char(xml_lex_t *this_)
{
    int c = fgetc(this_->file);
    if (c == '\n')
        this_->line_number++;
    return c;
}

void xml_lex_unget_char(xml_lex_t *this_, int c)
{
    if (c == EOF)
        return;
    if (c == '\n')
        this_->line_number--;
    ungetc(c, this_->file);
}

int xml_lex_peek_char(xml_lex_t *this_)
{
    int c = xml_lex_get_char(this_);
    xml_lex_unget_char(this_, c);
    return c;
}

void xml_lex_skip_spaces(xml_lex_t *this_)
{
    int c;

    while (c = xml_lex_get_char(this_), isblank_(c))
        ;
    xml_lex_unget_char(this_, c);
}

xml_token_t *xml_lex_get_word(xml_lex_t *this_)
{
	xml_token_t *token;
	text_t text;
    int c = xml_lex_get_char(this_);
    if (!(isalpha(c) || c == '_')) {
        xml_lex_unget_char(this_, c);
        return NULL;
    }

    text_init(&text);
    text_put_char(&text, c);
    while (c = xml_lex_get_char(this_), (isalnum(c) || c == '_'))
        text_put_char(&text, c);
    xml_lex_unget_char(this_, c);

    token = xml_token_new(XML_TOKEN_SYMBOL, text.data);
    text_destroy(&text);
    return token;
}

static int is_digit(int c)
{
    return c == '-' || c == '.' || isdigit(c);
}

xml_token_t *xml_lex_get_double(xml_lex_t *this_)
{
	xml_token_t *token;
	text_t text;
    int c = xml_lex_get_char(this_);
    if (!is_digit(c)) {
        xml_lex_unget_char(this_, c);
        return 0;
    }

    text_init(&text);
    text_put_char(&text, c);
    while (c = xml_lex_get_char(this_), is_digit(c))
        text_put_char(&text, c);
    xml_lex_unget_char(this_, c);

    token = xml_token_new(XML_TOKEN_DOUBLE, text.data);
    text_destroy(&text);
    return token;
}

xml_token_t *xml_lex_get_string(xml_lex_t *this_)
{
	xml_token_t *token;
	text_t text;
	int quote;
    int c = xml_lex_get_char(this_);
    if (c != '\'' && c != '"') {
        xml_lex_unget_char(this_, c);
        return 0;
    }
    quote = c;

    text_init(&text);
    while (c = xml_lex_get_char(this_), (c != EOF && c != quote)) {
        if (c == '\\') {
            int d = xml_lex_get_char(this_);
            switch (d) {
                case 'n':
                    c = '\n';
                    break;

                case 'r':
                    c = '\r';
                    break;

                case 't':
                    c = '\t';
                    break;

                default:
                    c = d;
            }
        }
        text_put_char(&text, c);
    }
    assert(c == quote);

    token = xml_token_new(XML_TOKEN_STRING, text.data);
    token->svalue = strdup(text.data);
    text_destroy(&text);
    return token;
}

int xml_lex_count_tabs(xml_lex_t *this_, text_t *text)
{
	char *p;
    int spaces = 0;

    for (p = text->data; p < text->data + text->size; p++) {
        switch (*p) {
            case ' ':
                spaces++;
                break;

            default:
                assert(0);
        } 
    }

    return spaces / this_->tab_length; 
}

void xml_lex_read_tabs(xml_lex_t *this_)
{
	int i;
    int count;
    xml_token_t *token;
	int last_tabs;
	int this_tabs;
    int c;
    text_t text;

    text_init(&text);
    while (c = xml_lex_get_char(this_), isblank_(c))
        text_put_char(&text, c);
    xml_lex_unget_char(this_, c);
    this_tabs = xml_lex_count_tabs(this_, &text);
    last_tabs = this_->last_tabs; 
    text_destroy(&text);

    // Ignore empty line
    if (c == '\n')
        return;

    if (this_tabs > last_tabs) {
        count = this_tabs - last_tabs;
        token = xml_token_new(XML_TOKEN_PUSH, NULL);
    } else {
        count = last_tabs - this_tabs;
        token = xml_token_new(XML_TOKEN_POP, NULL);
    }

    for (i = 0; i < count; i++)
        stack_push(&this_->token_stack, token);
    this_->last_tabs = this_tabs; 
}

xml_token_t *xml_lex_meet_eof(xml_lex_t *this_)
{
	int i;
    for (i = 0; i < this_->last_tabs; i++) {
        xml_token_t *token = xml_token_new(XML_TOKEN_PUSH, NULL);
        stack_push(&this_->token_stack, token);
    }
    this_->last_tabs = 0;

    if (stack_is_empty(&this_->token_stack))
        return NULL;
    else
        return stack_pop(&this_->token_stack);
}

xml_token_t *xml_lex_get_token(xml_lex_t *this_)
{
	int c;
    xml_token_t *token;

    if (!stack_is_empty(&this_->token_stack))
        return stack_pop(&this_->token_stack);

    c = xml_lex_peek_char(this_);
    if (c == EOF)
        return xml_lex_meet_eof(this_);

    xml_lex_skip_spaces(this_);
    c = xml_lex_get_char(this_);
    if (c == '\n') {
        xml_lex_read_tabs(this_);
        return xml_token_new(XML_TOKEN_NEWLINE, "\\n");
    }
    xml_lex_unget_char(this_, c);

    if (token = xml_lex_get_word(this_)) 
        return token;
    if (token = xml_lex_get_double(this_))
        return token;
    if (token = xml_lex_get_string(this_))
        return token;

    xml_lex_error(this_, "unknown character '%c'\n", c);
    return NULL;
}

void xml_lex_unget_token(xml_lex_t *this_, xml_token_t *token)
{
    stack_push(&this_->token_stack, token);
}

void xml_lex_dump(xml_lex_t *this_)
{
    xml_token_t *token;

    while (token = xml_lex_get_token(this_))
        xml_token_dump(token);
}
