#include "root.h"
#include "lex.h"
#include "ast.h"
#include "gram.tab.h"

char *ast_name_array[] = {
    /* 00 */  "module",
    /* 01 */  "clause_list",
    /* 02 */  "clause",
    /* 03 */  "express_clause",
    /* 04 */  "assign_clause",
    /* 05 */  "del_clause",
    /* 06 */  "pass_clause",
    /* 07 */  "import_clause",
    /* 08 */  "from_clause",
    /* 09 */  "global_clause",
    /* 10 */  "print_clause",
    /* 11 */  "assert_clause",
    /* 12 */  "break_clause",
    /* 13 */  "continue_clause",
    /* 14 */  "return_clause",
    /* 15 */  "group_clause",
    /* 16 */  "if_clause",
    /* 17 */  "elif_clause",
    /* 18 */  "else_clause",
    /* 19 */  "while_clause",
    /* 20 */  "for_clause",
    /* 21 */  "try_clause",
    /* 22 */  "except_clause",
    /* 23 */  "finally_clause",
    /* 24 */  "raise_clause",
    /* 25 */  "def_clause",
    /* 26 */  "param_list",
    /* 27 */  "class_clause",
    /* 28 */  "lambda_express",
    /* 29 */  "slice_express",
    /* 30 */  "binary_express",
    /* 31 */  "unary_express",
    /* 32 */  "call_express",
    /* 33 */  "arg_list",
    /* 34 */  "id_list",
    /* 35 */  "item_express",
    /* 36 */  "field_express",
    /* 37 */  "postfix_express",
    /* 38 */  "token",
    /* 39 */  "list_express",
    /* 40 */  "dict_express",
    /* 41 */  "dict_item",
    /* 42 */  "tuple_express",
};

void ast_token_dump(ast_t *this_, xml_file_t *xml_file)
{
    switch (this_->token) {
        case TOKEN_DOUBLE_CONST:
            xml_file_dump(xml_file, "%f", this_->dvalue);
            break;

        case TOKEN_STRING_CONST:
            xml_file_dump(xml_file, "\"%s\"", this_->svalue);
            break;

        default:
            xml_file_dump(xml_file, "%s", this_->svalue);
    }
}

char *ast_name(ast_t *this_)
{
    return ast_name_array[this_->type];
}

void ast_dump(ast_t *this_, xml_file_t *xml_file)
{
	int i;
    ast_t *child;
    char *name;
    assert(this_ != NULL);
    xml_file_printf(xml_file, "%3d: ", this_->line_number);

    if (this_->type == AST_TOKEN) {
        ast_token_dump(this_, xml_file);
		return;
	}

    name = ast_name(this_);
    xml_file_dump(xml_file, "%s", name);
    xml_file_push(xml_file);

    ast_each_child (this_, i, child) {
        if (child == NULL)
            continue;
        ast_dump(child, xml_file);
    }

    xml_file_pop(xml_file);
}

int ast_is_left_value(ast_t *this_)
{
    switch (this_->type) {
        case AST_ITEM_EXPRESS:
        case AST_FIELD_EXPRESS:
            return 1;

        case AST_TOKEN:
            if (this_->token == TOKEN_ID)
                return 1;
    } 
    return 0;
}

int ast_is_token(ast_t *this_, int token)
{
    return this_->type == AST_TOKEN && this_->token == token;
}

ast_t *ast_new(int type, int count, ...)
{
    va_list ap;
    ast_t *this_ = malloc(sizeof(ast_t));
    this_->type = type;
    this_->file_name = NULL;
    this_->line_number = 0;

    this_->token = 0;
    this_->svalue = NULL;
    vector_init(&this_->child_vector);

    va_start(ap, count);
    while (count--) {
        ast_t *child = va_arg(ap, ast_t*);
        ast_add_child(this_, child);
    }
    va_end(ap);
    return this_;
}

ast_t *ast_new_token(int token)
{
    ast_t *this_ = ast_new(AST_TOKEN, 0);
    this_->token = token;
    return this_;
}

ast_t *ast_new_double(double dvalue)
{
    ast_t *this_ = ast_new(AST_TOKEN, 0);
    this_->token = TOKEN_DOUBLE_CONST;
    this_->dvalue = dvalue;
    return this_;
}

ast_t *ast_new_id(char *svalue)
{
    ast_t *this_ = ast_new_token(TOKEN_ID);
    this_->svalue = strdup(svalue);
    return this_;
}

ast_t *ast_add_child(ast_t *this_, ast_t *child)
{
    vector_push_back(&this_->child_vector, child);
    return this_;
}

ast_t *ast_prepend_child(ast_t *this_, ast_t *child)
{
	int i;
	int vector_count;
	ast_t **vector;
    vector_push_back(&this_->child_vector, NULL);

    vector = this_->child_vector.data;
    vector_count = this_->child_vector.count;
    for (i = vector_count - 1; i >= 1; i--)
        vector[i] = vector[i - 1];
    vector[0] = child;
    return this_;
}

int ast_child_count(ast_t *this_)
{
    return this_->child_vector.count;
}

ast_t *ast_get_child(ast_t *this_, int index)
{
    ast_t *child = vector_get(&this_->child_vector, index);
    return child;
}

void ast_set_child(ast_t *this_, int index, ast_t *child)
{
    vector_set(&this_->child_vector, index, child);
}

ast_t *ast_get_last_child(ast_t *this_)
{
	ast_t *child;
    int index = this_->child_vector.count - 1;
    if (index < 0)
        return NULL;
    child = ast_get_child(this_, index);
    return child;
}

void ast_locate(ast_t *this_, char *file_name)
{
    int i;
    ast_t *child;

    this_->file_name = file_name;
    ast_each_child (this_, i, child) {
        if (child == NULL)
            continue;
        ast_locate(child, file_name);
        if (this_->line_number == 0)
            this_->line_number = child->line_number;
    }
}
