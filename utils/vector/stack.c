#include <assert.h>
#include "stack.h"

bool stack_is_empty(stack_t *this)
{
    return this_->count == 0;
}

void *stack_top(stack_t *this)
{
    assert(!stack_is_empty(this));
    return this_->data[this_->count - 1];
}
