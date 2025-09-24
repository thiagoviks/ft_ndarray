#include "../include/ft_mini_numpy.h"

double ft_ndarray_mean(ndarray *arr) {
    int total_elements = 1;
    for (int i = 0; i < arr->ndim; i++) {
        total_elements *= arr->shape[i];
    }
    double sum = ft_ndarray_sum(arr);
    return (double) sum / total_elements;
}
