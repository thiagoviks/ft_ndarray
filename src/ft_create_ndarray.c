#include "../include/ft_ndarray.h"

ndarray *ft_create_ndarray(int *shape, int ndim, ft_size_t itemsize) {
  ndarray *arr = ft_malloc(sizeof(ndarray));
  if (!arr)
    return (FT_NULL);

  arr->ndim = ndim;
  arr->shape = ft_malloc(sizeof(int) * ndim);
  if (!arr->shape) {
    ft_free(arr);
    return (FT_NULL);
  }

  ft_size_t total_size = 1;
  for (int i = 0; i < ndim; i++) {
    arr->shape[i] = shape[i];
    total_size *= shape[i];
  }

  arr->itemsize = itemsize;
  arr->data = ft_malloc(total_size * itemsize);

  if (!arr->data) {
    ft_free(arr->shape);
    ft_free(arr);
    return (FT_NULL);
  }

  return (arr);
}
