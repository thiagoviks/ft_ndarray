#include "ft_mini_numpy.h"

int ft_ndarray_max(ndarray *arr) {
    int max_val = *((int*)arr->data);
    int total_elements = 1;
    for (int i = 0; i < arr->ndim; i++) {
        total_elements *= arr->shape[i];
    }
    for (int i = 0; i < total_elements; i++) {
        int value = *((int*)arr->data + i);
        if (value > max_val) {
            max_val = value;
        }
    }
    return max_val;
}

int ft_ndarray_min(ndarray *arr) {
    int min_val = *((int*)arr->data);
    int total_elements = 1;
    for (int i = 0; i < arr->ndim; i++) {
        total_elements *= arr->shape[i];
    }
    for (int i = 0; i < total_elements; i++) {
        int value = *((int*)arr->data + i);
        if (value < min_val) {
            min_val = value;
        }
    }
    return min_val;
}
