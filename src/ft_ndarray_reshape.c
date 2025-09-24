#include "../include/ft_mini_numpy.h"

ndarray* ft_ndarray_reshape(ndarray *arr, int *new_shape, int new_ndim) {
    int total_elements = 1;
    for (int i = 0; i < new_ndim; i++) {
        total_elements *= new_shape[i];
    }
    int current_total_elements = 1;
    for (int i = 0; i < arr->ndim; i++) {
        current_total_elements *= arr->shape[i];
    }
    if (current_total_elements != total_elements) {
        // Ensure the total number of elements is the same
        return NULL;
    }

    ndarray* reshaped_arr = ft_create_ndarray(new_shape, new_ndim, arr->itemsize);
    ft_memcpy(reshaped_arr->data, arr->data, total_elements * arr->itemsize);
    return reshaped_arr;
}
