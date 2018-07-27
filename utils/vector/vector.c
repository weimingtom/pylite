#include <stdlib.h>
#include <assert.h>
#include "vector.h"

void vector_init(vector_t *this)
{
    this_->count = 0;
    this_->capacity = 4;
    this_->data = malloc(this_->capacity * sizeof(void *));
    for (int i = 0; i < this_->capacity; i++)
        this_->data[i] = NULL;
}

void vector_destroy(vector_t *this)
{
    free(this_->data);
}

void vector_push_back(vector_t *this, void *item)
{
    if (this_->count >= this_->capacity) {
        this_->capacity *= 2;
        int size = this_->capacity * sizeof(void *);
        this_->data = realloc(this_->data, size);
    }

    this_->data[this_->count] = item;
    this_->count++;
}

void *vector_pop_back(vector_t *this)
{
    assert(this_->count > 0);
    this_->count--;
    void *item = this_->data[this_->count];
    this_->data[this_->count] = NULL;
    return item;
}

void *vector_get(vector_t *this, int index)
{
    assert(index < this_->count);
    return this_->data[index];
}

void vector_set(vector_t *this, int index, void *item)
{
    assert(index < this_->count);
    this_->data[index] = item;
}
