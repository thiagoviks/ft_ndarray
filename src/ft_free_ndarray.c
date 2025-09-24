#include "../include/ft_mini_numpy.h"

void ft_free_ndarray(ndarray *arr) {
    if (!arr) return;
    ft_free(arr->shape);
    ft_free(arr->data);
    ft_free(arr);
}
