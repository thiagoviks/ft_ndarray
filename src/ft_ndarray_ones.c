#include "ft_mini_numpy.h"

ndarray* ft_ndarray_ones(int *shape, int ndim, size_t itemsize) {
    ndarray *arr = ft_create_ndarray(shape, ndim, itemsize);
    int total_elements = 1;
    for (int i = 0; i < ndim; i++) {
        total_elements *= shape[i];
    }
    for (int i = 0; i < total_elements; i++) {
        *((int*)arr->data + i) = 1;  // Cast to the proper type based on itemsize
    }
    return arr;
}
