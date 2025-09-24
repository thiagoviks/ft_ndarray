#include "ft_mini_numpy.h"

ndarray* ft_create_ndarray_with_strides(int *shape, int ndim, size_t itemsize) {
    ndarray* arr = (ndarray*) ft_malloc(sizeof(ndarray));
    arr->shape = (int*) ft_malloc(ndim * sizeof(int));
    arr->strides = (int*) ft_malloc(ndim * sizeof(int));
    for (int i = 0; i < ndim; i++) {
        arr->shape[i] = shape[i];
    }

    // Calculate strides
    int stride = 1;
    for (int i = ndim - 1; i >= 0; i--) {
        arr->strides[i] = stride;
        stride *= shape[i];
    }

    arr->ndim = ndim;
    arr->itemsize = itemsize;

    int total_elements = stride;
    arr->data = ft_malloc(total_elements * itemsize);
    return arr;
}
