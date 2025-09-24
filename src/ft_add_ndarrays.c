#include "ft_mini_numpy.h"

void ft_add_ndarrays(ndarray *a, ndarray *b, ndarray *result) {
    if (!a || !b || !result) return;
    
    size_t total_size = 1;
    for (int i = 0; i < a->ndim; i++)
        total_size *= a->shape[i];

    if (a->itemsize == sizeof(int)) {
        int *data_a = (int *)a->data;
        int *data_b = (int *)b->data;
        int *data_r = (int *)result->data;
        for (size_t i = 0; i < total_size; i++)
            data_r[i] = data_a[i] + data_b[i];
    } else if (a->itemsize == sizeof(double)) {
        double *data_a = (double *)a->data;
        double *data_b = (double *)b->data;
        double *data_r = (double *)result->data;
        for (size_t i = 0; i < total_size; i++)
            data_r[i] = data_a[i] + data_b[i];
    }
}
