#include "../include/ft_mini_numpy.h"

// Computes the dot product of two 1D arrays
double ft_dot_product(ndarray *a, ndarray *b) {
    if (!a || !b || a->ndim != 1 || b->ndim != 1 || a->shape[0] != b->shape[0])
        return 0.0; // Invalid input

    double sum = 0.0;
    int size = a->shape[0];

    if (a->itemsize == sizeof(int)) {
        int *data_a = (int *)a->data;
        int *data_b = (int *)b->data;
        for (int i = 0; i < size; i++)
            sum += data_a[i] * data_b[i];
    } else if (a->itemsize == sizeof(double)) {
        double *data_a = (double *)a->data;
        double *data_b = (double *)b->data;
        for (int i = 0; i < size; i++)
            sum += data_a[i] * data_b[i];
    }

    return sum;
}
