#include "../include/ft_mini_numpy.h"

double ft_ndarray_mean(ndarray *arr) {
    if (arr->itemsize != sizeof(double)) {
        fprintf(stderr, "ft_ndarray_mean: column is not of type double\n");
        return 0.0;
    }

    int total_elements = 1;
    for (int i = 0; i < arr->ndim; i++) {
        total_elements *= arr->shape[i];
    }

    double sum = 0.0;
    double *data = (double *)arr->data;
    for (int i = 0; i < total_elements; i++) {
        sum += data[i];
    }
    return sum / total_elements;
}
