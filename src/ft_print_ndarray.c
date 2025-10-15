#include "../include/ft_mini_numpy.h"

void ft_print_ndarray(ndarray *arr, char type) {
    if (!arr) return;
    ft_size_t total_size = 1;
    for (int i = 0; i < arr->ndim; i++)
        total_size *= arr->shape[i];

    ft_printf("[");
    if (type == 'i') { // Integer array
        int *data = (int *)arr->data;
        for (ft_size_t i = 0; i < total_size; i++)
            ft_printf("%d ", data[i]);
    } else if (type == 'd') { // Double array
        double *data = (double *)arr->data;
        for (ft_size_t i = 0; i < total_size; i++)
            ft_printf("%.2f ", data[i]);
    }
    ft_printf("]\n");
}
