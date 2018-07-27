#include "root.h"
#include "lex.h"
#include "ast.h"
#include "gram.tab.h"

#define isblank_(c) ((c) == ' ' || (c) == '\t')

void yyerror(lex_t *lex, ast_t **module, char *msg)
{
    fprintf(stderr, "SyntaxError:\n");
    fprintf(stderr, "  At %s, line %d\n", lex->file_name, lex->line_number);
    exit(EXIT_FAILURE);
}

void lex_error(lex_t *this_, char *format, ...)
{
    va_list ap;
    va_start(ap, format);

    fprintf(stderr, "SyntaxError: ");
    vfprintf(stderr, format, ap);
    fprintf(stderr, "\n");
    fprintf(stderr, "  At %s, line %d\n", this_->file_name, this_->line_number);
    va_end(ap);

    exit(EXIT_FAILURE);
}

keyword_t keyword_array[] = {
    {"if",         TOKEN_IF},
    {"elif",       TOKEN_ELIF},
    {"else",       TOKEN_ELSE},
    {"for",        TOKEN_FOR},
    {"while",      TOKEN_WHILE},
    {"in",         TOKEN_IN},
    {"continue",   TOKEN_CONTINUE},
    {"break",      TOKEN_BREAK},
    {"return",     TOKEN_RETURN},
    {"global",     TOKEN_GLOBAL},
    {"from",       TOKEN_FROM},
    {"import",     TOKEN_IMPORT},
    {"del",        TOKEN_DEL},
    {"pass",       TOKEN_PASS},
    {"print",      TOKEN_PRINT},
    {"assert",     TOKEN_ASSERT},
    {"try",        TOKEN_TRY},
    {"except",     TOKEN_EXCEPT},
    {"as",         TOKEN_AS},
    {"finally",    TOKEN_FINALLY},
    {"raise",      TOKEN_RAISE},
    {"class",      TOKEN_CLASS},
    {"def",        TOKEN_DEF},
    {"lambda",     TOKEN_LAMBDA},

    {"None",       TOKEN_NONE},
    {"True",       TOKEN_TRUE},
    {"False",      TOKEN_FALSE},
    {"not",        TOKEN_NOT},
    {"and",        TOKEN_AND},
    {"or",         TOKEN_OR},

    {"==",         TOKEN_EQ},
    {"!=",         TOKEN_NE},
    {">=",         TOKEN_GE},
    {"<=",         TOKEN_LE},
    {"<<",         TOKEN_LSH},
    {">>",         TOKEN_RSH},

    {"|=",         TOKEN_OR_ASSIGN},
    {"^=",         TOKEN_XOR_ASSIGN},
    {"&=",         TOKEN_AND_ASSIGN},
    {"+=",         TOKEN_ADD_ASSIGN},
    {"-=",         TOKEN_SUB_ASSIGN},
    {"*=",         TOKEN_MUL_ASSIGN},
    {"/=",         TOKEN_DIV_ASSIGN},
    {"%=",         TOKEN_MOD_ASSIGN},
    {"<<=",        TOKEN_LSH_ASSIGN},
    {">>=",        TOKEN_RSH_ASSIGN},

    {"\n",         '\n'},
    {"?",          '?'},
    {":",          ':'},
    {"=",          '='},
    {"|",          '|'},
    {"^",          '^'},
    {"&",          '&'},
    {"<",          '<'},
    {">",          '>'},
    {"+",          '+'},
    {"-",          '-'},
    {"*",          '*'},
    {"/",          '/'},
    {"%",          '%'},
    {"!",          '!'},
    {"~",          '~'},
    {".",          '.'},
    {",",          ','},
    {";",          ';'},
    {"(",          '('},
    {")",          ')'},
    {"{",          '{'},
    {"}",          '}'},
    {"[",          '['},
    {"]",          ']'},
};

#define KEYWORD_COUNT array_count(keyword_array)
char *operator_chars = "\n?:=|^&<>+-*/%!~.,;(){}[]";

int lex_is_operator(int c)
{
    return (c < 256) && strchr(operator_chars, c);
}

lex_t *lex_new(char *file_name)
{
    lex_t *this_ = malloc(sizeof(lex_t));
    FILE *file = fopen(file_name, "r");
    if (!file) {
        fprintf(stderr, "minipy: can't open file %s\n", file_name);
        exit(EXIT_FAILURE);
    }

    this_->file = file;
    this_->file_name = file_name;
    this_->line_number = 1;

    this_->last_tabs = 0;
    this_->tab_length = 4;
    stack_init(&this_->token_stack);
    return this_;
}

ast_t *lex_get_keyword(lex_t *this_, char *name)
{
    int i;

    for (i = 0; i < KEYWORD_COUNT; i++) {
        keyword_t *keyword = keyword_array + i;
        if (strcmp(keyword->name, name) == 0) {
            ast_t *token = ast_new_token(keyword->value);
            token->svalue = keyword->name;
            return token;
        }
    }
    return NULL;
}

int lex_get_char(lex_t *this_)
{
    int c = fgetc(this_->file);
    if (c == '\n')
        this_->line_number++;
    return c;
}

void lex_unget_char(lex_t *this_, int c)
{
    if (c == EOF)
        return;
    if (c == '\n')
        this_->line_number--;
    ungetc(c, this_->file);
}

int lex_peek_char(lex_t *this_)
{
    int c = lex_get_char(this_);
    lex_unget_char(this_, c);
    return c;
}

void lex_skip_spaces(lex_t *this_)
{
    int c;

    while (c = lex_get_char(this_), isblank_(c))
        ;
    lex_unget_char(this_, c);
}

void lex_skip_garbage(lex_t *this_)
{
    int c;

    while (c = lex_get_char(this_), isblank_(c))
        ;

    if (c == '#') {
        while (c = lex_get_char(this_), (c != EOF && c != '\n'))
            ;
    }

    lex_unget_char(this_, c);
}

ast_t *lex_get_word(lex_t *this_)
{
	ast_t *token;
    text_t text;
    int c = lex_get_char(this_);
    if (!(isalpha(c) || c == '_')) {
        lex_unget_char(this_, c);
        return NULL;
    }

    text_init(&text);
    text_put_char(&text, c);
    while (c = lex_get_char(this_), (isalnum(c) || c == '_'))
        text_put_char(&text, c);
    lex_unget_char(this_, c);

    token = lex_get_keyword(this_, text.data);
    if (token) {
        text_destroy(&text);
        return token;
    }

    token = ast_new_token(TOKEN_ID);
    token->svalue = strdup(text.data);
    text_destroy(&text);
    return token;
}

ast_t *lex_get_double(lex_t *this_)
{
    ast_t *token;
    text_t text;
    int sign = +1;
    int c = lex_get_char(this_);
    if (!isdigit(c)) {
        lex_unget_char(this_, c);
        return 0;
    }

    text_init(&text);
    text_put_char(&text, c);
    while (c = lex_get_char(this_), (isdigit(c) || c == '.'))
        text_put_char(&text, c);
    lex_unget_char(this_, c);

    token = ast_new_token(TOKEN_DOUBLE_CONST);
    token->dvalue = atof(text.data);
    text_destroy(&text);
    return token;
}

static int is_quote(int c)
{
    return c == '"' || c == '\'';
}

ast_t *lex_get_string(lex_t *this_)
{
	ast_t *token;
    text_t text;
    int c = lex_get_char(this_);
    if (!is_quote(c)) {
        lex_unget_char(this_, c);
        return 0;
    }

    text_init(&text);
    while (c = lex_get_char(this_), (c != EOF && !is_quote(c)))
        text_put_char(&text, c);
    assert(c != EOF);

    token = ast_new_token(TOKEN_STRING_CONST);
    token->svalue = strdup(text.data);
    text_destroy(&text);
    return token;
}

ast_t *lex_get_operator(lex_t *this_)
{
    text_t text;
    int c = lex_get_char(this_);
    if (!lex_is_operator(c)) {
        lex_unget_char(this_, c);
        return NULL;
    }

    text_init(&text);
    text_put_char(&text, c);
    while (c = lex_get_char(this_), lex_is_operator(c))
        text_put_char(&text, c);
    lex_unget_char(this_, c);

    while (1) {
        ast_t *token = lex_get_keyword(this_, text.data);
        if (token)
            return token;
        c = text_trim_char(&text);
        lex_unget_char(this_, c);
    }
    text_destroy(&text);
    return NULL;
}

int lex_guess_tabs(lex_t *this_, text_t *text)
{
	char *p;
    int tabs = 0;
    int spaces = 0;

    for (p = text->data; p < text->data + text->size; p++) {
        switch (*p) {
            case '\t':
                tabs++;
                break;

            case ' ':
                spaces++;
                break;

            default:
                assert(0);
        } 
    }

    if (spaces && tabs)
        lex_error(this_, "mix spaces and tabs");

    if (spaces)
        return spaces / this_->tab_length; 
    return tabs;
}

void lex_read_tabs(lex_t *this_)
{
	int this_tabs;
    int last_tabs; 
    int i;
	int c;
    text_t text;
	int count;
    ast_t *token;
    
    text_init(&text);
    while (c = lex_get_char(this_), isblank_(c))
        text_put_char(&text, c);
    lex_unget_char(this_, c);
    this_tabs = lex_guess_tabs(this_, &text);
    last_tabs = this_->last_tabs; 
    text_destroy(&text);

    /* Ignore empty line */
    if (c == '\n')
        return;

    /* Ignore comment */
    if (c == '#')
        return;

    if (this_tabs > last_tabs) {
        count = this_tabs - last_tabs;
        token = ast_new_token(TOKEN_BEGIN);
    } else {
        count = last_tabs - this_tabs;
        token = ast_new_token(TOKEN_END);
    }

	for (i = 0; i < count; i++)
        stack_push(&this_->token_stack, token);
    this_->last_tabs = this_tabs; 
}

ast_t *lex_meet_eof(lex_t *this_)
{
	int i;
    for (i = 0; i < this_->last_tabs; i++) {
        ast_t *token = ast_new_token(TOKEN_BEGIN);
        stack_push(&this_->token_stack, token);
    }
    this_->last_tabs = 0;

    if (stack_is_empty(&this_->token_stack))
        return NULL;
    else
        return stack_pop(&this_->token_stack);
}

ast_t *lex_fetch_token(lex_t *this_)
{
    int c;
    ast_t *token;

    if (!stack_is_empty(&this_->token_stack))
        return stack_pop(&this_->token_stack);

    c = lex_peek_char(this_);
    if (c == EOF)
        return lex_meet_eof(this_);

    lex_skip_garbage(this_);
    c = lex_get_char(this_);
    if (c == '\n') {
        lex_read_tabs(this_);
        return ast_new_token('\n');
    }
    lex_unget_char(this_, c);

    if (token = lex_get_word(this_)) 
        return token;
    if (token = lex_get_operator(this_))
        return token;
    if (token = lex_get_double(this_))
        return token;
    if (token = lex_get_string(this_))
        return token;

    lex_error(this_, "unknown character");
    return NULL;
}

ast_t *lex_get_token(lex_t *this_)
{
    ast_t *token = lex_fetch_token(this_);
    if (token != NULL) {
        token->file_name = this_->file_name;
        token->line_number = this_->line_number;
    }
    return token;
}

void token_dump(ast_t *ast)
{
	int i;
    int token = ast->token;

    if (lex_is_operator(token)) {
        if (token == '\n') 
            printf("OP   \\n\n");
        else
            printf("OP   %c\n", token);
        return;
    }

    for (i = 0; i < KEYWORD_COUNT; i++) {
        keyword_t *keyword = keyword_array + i; 
        if (keyword->value == token) {
            printf("KEY  %s\n", keyword->name);
            return;
        }
    }
 
    switch (token) {
        case TOKEN_ID:
            printf("ID      %s\n", ast->svalue);
            break;

        case TOKEN_DOUBLE_CONST:
            printf("NUMBER  %lf\n", ast->dvalue);
            break;

        case TOKEN_STRING_CONST:
            printf("STRING  \"%s\"\n", ast->svalue);
            break;

        case TOKEN_BEGIN:
            puts("BEGIN");
            break;

        case TOKEN_END:
            puts("END");
            break;

        default:
            assert(0);
    }
}

void lex_dump(lex_t *this_)
{
    ast_t *token;

    while (token = lex_get_token(this_))
        token_dump(token);
}
