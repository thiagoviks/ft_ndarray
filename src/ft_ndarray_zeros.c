#include "../include/ft_mini_numpy.h"

ndarray* ft_ndarray_zeros(int *shape, int ndim, ft_size_t itemsize) {
    ndarray *arr = ft_create_ndarray(shape, ndim, itemsize);
    int total_elements = 1;
    for (int i = 0; i < ndim; i++) {
        total_elements *= shape[i];
    }
    ft_memset(arr->data, 0, total_elements * itemsize);
    return (arr);
}
