#include "../include/ft_ndarray.h"

ndarray *ft_ndarray_concatenate(ndarray *a, ndarray *b) {
  if (a->shape[0] != b->shape[0]) {
    // Only works for arrays with the same first dimension
    return (FT_NULL);
  }
  int new_shape[2] = {a->shape[0], a->shape[1] + b->shape[1]};
  ndarray *result = ft_create_ndarray(new_shape, 2, a->itemsize);
  for (int i = 0; i < a->shape[0]; i++) {
    for (int j = 0; j < a->shape[1]; j++) {
      *((int *)result->data + i * new_shape[1] + j) =
          *((int *)a->data + i * a->shape[1] + j);
    }
    for (int j = 0; j < b->shape[1]; j++) {
      *((int *)result->data + i * new_shape[1] + a->shape[1] + j) =
          *((int *)b->data + i * b->shape[1] + j);
    }
  }
  return (result);
}
