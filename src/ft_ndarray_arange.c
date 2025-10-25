#include "../include/ft_ndarray.h"

ndarray *ft_ndarray_arange(int start, int stop, int step, int *shape, int ndim,
                           ft_size_t itemsize) {
  int size = (stop - start) / step;
  shape[0] = size; // Set the shape to the appropriate size
  ndarray *arr = ft_create_ndarray(shape, ndim, itemsize);
  for (int i = 0; i < size; i++) {
    *((int *)arr->data + i) = start + i * step;
  }
  return (arr);
}
