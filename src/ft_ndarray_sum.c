#include "../include/ft_mini_numpy.h"

//this version only work with simple array 
// double ft_ndarray_sum(ndarray *arr) {
//     double sum = 0;
//     int total_elements = 1;
//     for (int i = 0; i < arr->ndim; i++) {
//         total_elements *= arr->shape[i];
//     }

//     if (arr->itemsize == sizeof(int)) {
//         int *data = (int*)arr->data;
//         for (int i = 0; i < total_elements; i++) {
//             sum += data[i];
//         }
//     }
//     else if (arr->itemsize == sizeof(float)) {
//         float *data = (float*)arr->data;
//         for (int i = 0; i < total_elements; i++) {
//             sum += data[i];
//         }
//     }
//     else if (arr->itemsize == sizeof(double)) {
//         double *data = (double*)arr->data;
//         for (int i = 0; i < total_elements; i++) {
//             sum += data[i];
//         }
//     }
//     else {
//         ft_printf("Unsupported item size\n");
//         return 0;
//     }

//     return sum;
// }

double ft_ndarray_sum(ndarray *arr) {
    double sum = 0.0;

    int total_elements = 1;
    for (int i = 0; i < arr->ndim; i++) {
        total_elements *= arr->shape[i];
    }

    for (int i = 0; i < total_elements; i++) {
        // Usa strides para achar o endereço certo
        char *ptr = (char *)arr->data;
        int idx = i;
        for (int d = arr->ndim - 1; d >= 0; d--) {
            int coord = idx % arr->shape[d];
            ptr += coord * arr->strides[d];
            idx /= arr->shape[d];
        }
        sum += *((double *)ptr);
    }

    return sum;
}
