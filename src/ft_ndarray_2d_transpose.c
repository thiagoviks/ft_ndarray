#include "../include/ft_mini_numpy.h"

ndarray *ft_ndarray_2d_transpose(ndarray *a) {
    if (!a || a->ndim != 2)
        return NULL; // Only 2D matrices are supported

    int new_shape[2] = {a->shape[1], a->shape[0]};
    ndarray *result = ft_create_ndarray(new_shape, 2, a->itemsize);
    if (!result)
        return NULL;

    int rows = a->shape[0];
    int cols = a->shape[1];

    if (a->itemsize == sizeof(int)) {
        int *data_a = (int *)a->data;
        int *data_r = (int *)result->data;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                data_r[j * rows + i] = data_a[i * cols + j];
            }
        }
    } else if (a->itemsize == sizeof(double)) {
        double *data_a = (double *)a->data;
        double *data_r = (double *)result->data;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                data_r[j * rows + i] = data_a[i * cols + j];
            }
        }
    }
    return result;
}
