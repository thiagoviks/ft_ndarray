#include "../include/ft_ndarray.h"

void ft_free_ndarray(ndarray *arr) {
  if (!arr)
    return;
  ft_free(arr->shape);
  ft_free(arr->data);
  ft_free(arr);
}
