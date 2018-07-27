#include <assert.h>
#include <stddef.h>
#include "list.h"

void chain_init(chain_t *this_)
{
    this_->next = this_->prev = NULL;
}

void chain_link(chain_t *left, chain_t *right)
{
    left->next = right;
    right->prev = left;
}

void chain_link3(chain_t *left, chain_t *chain, chain_t *right)
{
    chain_link(left, chain);
    chain_link(chain, right);
}

void chain_unlink(chain_t *this_)
{
    chain_link(this_->prev, this_->next);
    this_->next = NULL;
    this_->prev = NULL;
}

void chain_prepend(chain_t *this_, chain_t *new_chain)
{
    chain_link3(this_->prev, new_chain, this_);
}

void chain_append(chain_t *this_, chain_t *new_chain)
{
    chain_link3(this_, new_chain, this_->next);
}

void list_init(list_t *this_)
{
    this_->next = this_->prev = this_;
}

int list_empty(list_t *this_)
{
    return this_->next == this_;
}

chain_t *list_head(list_t *this_)
{
    if (this_->next == this_)
        return NULL;
    return this_->next;
}

chain_t *list_tail(list_t *this_)
{
    if (this_->next == this_)
        return NULL;
    return this_->prev;
}

void list_push_head(list_t *this_, chain_t *chain)
{
    assert(chain->next == NULL);
    chain_link3(this_, chain, this_->next); 
}

chain_t *list_pop_head(list_t *this_)
{
	chain_t *head;
    if (list_empty(this_))
        return NULL;
    head = this_->next;
    chain_unlink(head);
    return head;
}

void list_push_tail(list_t *this_, chain_t *chain)
{
    assert(chain->next == NULL);
    chain_link3(this_->prev, chain, this_); 
}

chain_t *list_pop_tail(list_t *this_)
{
	chain_t *tail;
    if (list_empty(this_))
        return NULL;
    tail = this_->prev;
    chain_unlink(tail);
    return tail;
}

void chain_remove(void *chain)
{
    chain_unlink((chain_t *)chain);
}

void *list_front(list_t *this_)
{
    return list_head(this_);
}

void *list_back(list_t *this_)
{
    return list_tail(this_);
}

void list_push_front(list_t *this_, void *item)
{
    list_push_head(this_, (chain_t *)item);
}

void list_push_back(list_t *this_, void *item)
{
    list_push_tail(this_, (chain_t *)item);
}

void *list_pop_front(list_t *this_)
{
    void *item = list_pop_head(this_);
    return item;
}

void *list_pop_back(list_t *this_)
{
    void *item = list_pop_tail(this_);
    return item;
}
