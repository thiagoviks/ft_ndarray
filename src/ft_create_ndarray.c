#include "ft_mini_numpy.h"

// Global memory pool
memory_pool *global_pool = NULL;
void *ft_memory_pool_alloc(size_t size) {
    if (global_pool == NULL || global_pool->used + size > global_pool->size) {
        // If the global pool is not initialized or not enough space, allocate new memory pool
        memory_pool *new_pool = (memory_pool*) ft_malloc(sizeof(memory_pool));
        new_pool->size = size > 1024 * 1024 ? size : 1024 * 1024; // minimum 1MB block
        new_pool->used = 0;
        new_pool->memory = ft_malloc(new_pool->size);
        new_pool->next = global_pool;
        global_pool = new_pool;
    }

    void *ptr = (char*)global_pool->memory + global_pool->used;
    global_pool->used += size;
    return ptr;
}

void ft_memory_pool_free() {
    while (global_pool != NULL) {
        memory_pool *temp = global_pool;
        global_pool = global_pool->next;
        ft_free(temp->memory);
        ft_free(temp);
    }
}

ndarray *ft_create_ndarray(int *shape, int ndim, size_t itemsize) {
    ndarray *arr = ft_malloc(sizeof(ndarray));
    if (!arr) return NULL;

    arr->ndim = ndim;
    arr->shape = ft_malloc(sizeof(int) * ndim);
    if (!arr->shape) {
        ft_free(arr);
        return NULL;
    }

    size_t total_size = 1;
    for (int i = 0; i < ndim; i++) {
        arr->shape[i] = shape[i];
        total_size *= shape[i];
    }

    arr->itemsize = itemsize;
    arr->data = ft_malloc(total_size * itemsize);
    //arr->data = ft_memory_pool_alloc(ft_calculate_total_elements(shape, ndim) * itemsize);
    if (!arr->data) {
        ft_free(arr->shape);
        ft_free(arr);
        return NULL;
    }
    
    return arr;

    // //implementation with memory pool
    // ndarray *arr = (ndarray*) ft_malloc(sizeof(ndarray));
    // arr->shape = (int*) ft_malloc(ndim * sizeof(int));
    // ft_memcpy(arr->shape, shape, ndim * sizeof(int));
    // arr->ndim = ndim;
    // arr->itemsize = itemsize;
    // arr->data = ft_memory_pool_alloc(ft_calculate_total_elements(shape, ndim) * itemsize);
    // return arr;
}
