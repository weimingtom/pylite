#include "root.h"
#include "gc.h"
#include "alloc.h"

void *gc_memory_low;
void *gc_memory_mid;
void *gc_memory_high;
int gc_memory_size;

gc_pool_t gc_small_pool;
gc_pool_t gc_large_pool;
void *gc_object_list;

int gc_guess_object(void *p)
{
    if (gc_memory_low <= p && p < gc_memory_mid) {
		py_object_t *py_object;
		unsigned long offset = (unsigned long)((char *)p - (char *)gc_memory_low);
        if (offset % GC_SMALL_SIZE != 0)
            return 0;
        py_object = p;
        return (py_object->flags & GC_MAGIC) == GC_LIVE_MAGIC;
    }

    if (gc_memory_mid <= p && p < gc_memory_high) {
		py_object_t *py_object;
        unsigned long offset = (unsigned long)((char *)p - (char *)gc_memory_mid);
        if (offset % GC_LARGE_SIZE != 0)
            return 0;
        py_object = p;
        return (py_object->flags & GC_MAGIC) == GC_LIVE_MAGIC;
    }

    return 0;
}

static __inline void *gc_pool_alloc(gc_pool_t *this_, int object_size)
{
	py_object_t *py_object;
    assert(object_size <= this_->object_size);

    py_object = this_->object_list;
    if (py_object == NULL) {
        return NULL;
    }
    this_->object_list = ((py_object_t *)this_->object_list)->next;
    py_object->flags = GC_LIVE_MAGIC;
    py_object->next = gc_object_list;
    gc_object_list = py_object; 

    return py_object;
}

static __inline void gc_pool_free(gc_pool_t *this_, py_object_t *py_object)
{
#ifndef NDEBUG
    memset(py_object, 0, this_->object_size);
#endif
    py_object->flags = GC_DEAD_MAGIC;
    py_object->next = this_->object_list;
    this_->object_list = py_object;
}

void gc_pool_init(gc_pool_t *this_, int object_size, 
                  void *memory_low, void *memory_high)
{
	char *py_object;
    this_->object_size = object_size;
    this_->memory_low = memory_low;
    this_->memory_high = memory_high;

    py_object = memory_low; 
    for (; py_object < (char *)memory_high; py_object += object_size)
        gc_pool_free(this_, (py_object_t *)py_object);
}

py_object_t *gc_alloc_object(int size)
{
    py_object_t *py_object;

    if (size <= GC_SMALL_SIZE)
        py_object = gc_pool_alloc(&gc_small_pool, size);
    else
        py_object = gc_pool_alloc(&gc_large_pool, size);
    if (py_object != NULL)
        return py_object;

    gc_start();
    if (size <= GC_SMALL_SIZE)
        py_object = gc_pool_alloc(&gc_small_pool, size);
    else
        py_object = gc_pool_alloc(&gc_large_pool, size);
    if (py_object == NULL) {
        fprintf(stderr, "gc failed!\n");
        exit(EXIT_FAILURE);
    }
    return py_object;
}

void gc_free_object(py_object_t *py_object)
{
	void *data;
    py_class_t *py_class = py_object->py_class;
    if (py_class && py_class->gc_free)
        py_class->gc_free(py_object);

    data = py_object->field_vector.data;
    if (data != NULL)
        free(data);

    if (((void *)py_object) < gc_memory_mid)
        gc_pool_free(&gc_small_pool, py_object);
    else
        gc_pool_free(&gc_large_pool, py_object);
}

void gc_setup(int object_count)
{
	int error;
    void *address;
    int small_count = object_count * 15 / 16;
    int large_count = object_count * 1 / 16;
    gc_memory_size = small_count * GC_SMALL_SIZE + large_count * GC_LARGE_SIZE;

#ifndef _MSC_VER
    error = posix_memalign(&address, CACHE_SIZE, gc_memory_size);
#else
	address = _aligned_malloc(gc_memory_size, CACHE_SIZE);
	error = address != 0 ? 0 : 1;
#endif
    if (error != 0) {
        fprintf(stderr, "gc_setup failed!\n");
        exit(EXIT_FAILURE);
    }

    gc_memory_low = address;
    gc_memory_mid = (char *)address + small_count * GC_SMALL_SIZE;
	gc_memory_high = (char *)address + gc_memory_size;

    gc_object_list = NULL;
    gc_pool_init(&gc_small_pool, GC_SMALL_SIZE, gc_memory_low, gc_memory_mid);
    gc_pool_init(&gc_large_pool, GC_LARGE_SIZE, gc_memory_mid, gc_memory_high);
}
