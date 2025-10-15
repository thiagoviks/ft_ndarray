#include "../include/ft_mini_numpy.h"

void ft_scalar_multiply(ndarray *a, double scalar) {
    if (!a) return;
    
    ft_size_t total_size = 1;
    for (int i = 0; i < a->ndim; i++)
        total_size *= a->shape[i];

    if (a->itemsize == sizeof(int)) {
        int *data = (int *)a->data;
        for (ft_size_t i = 0; i < total_size; i++)
            data[i] *= (int)scalar;
    } else if (a->itemsize == sizeof(double)) {
        double *data = (double *)a->data;
        for (ft_size_t i = 0; i < total_size; i++)
            data[i] *= scalar;
    }
}
