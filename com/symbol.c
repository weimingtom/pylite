#include "root.h"
#include "symbol.h"
#include "scope.h"

symbol_t *symbol_new(int type, char *name)
{
    symbol_t *this_ = malloc(sizeof(symbol_t));
    chain_init(&this_->chain);
    this_->type = type;
    this_->name = strdup(name);
    this_->offset = 0;
    return this_;
}

void symbol_dump(symbol_t *this_, xml_file_t *xml_file)
{
	char *text = NULL;

	xml_file_dump(xml_file, "symbol");
    xml_file_push(xml_file);

    switch (this_->type) {
        case SCOPE_GLOBAL:
            text = "SCOPE_GLOBAL";
            break;

        case SCOPE_CLASS:
            text = "SCOPE_CLASS";
            break;

        case SCOPE_LOCAL:
            text = "SCOPE_LOCAL";
            break;
    }
    xml_file_dump(xml_file, "type %s", text);
    xml_file_dump(xml_file, "name %s", this_->name);
    xml_file_dump(xml_file, "offset %d", this_->offset);
    xml_file_pop(xml_file);
}
