#include "ft_mini_numpy.h"

void ft_print_ndarray(ndarray *arr, char type) {
    if (!arr) return;
    size_t total_size = 1;
    for (int i = 0; i < arr->ndim; i++)
        total_size *= arr->shape[i];

    printf("[");
    if (type == 'i') { // Integer array
        int *data = (int *)arr->data;
        for (size_t i = 0; i < total_size; i++)
            printf("%d ", data[i]);
    } else if (type == 'd') { // Double array
        double *data = (double *)arr->data;
        for (size_t i = 0; i < total_size; i++)
            printf("%.2f ", data[i]);
    }
    printf("]\n");
}
