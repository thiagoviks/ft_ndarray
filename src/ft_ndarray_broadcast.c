#include "../include/ft_mini_numpy.h"

// Helper function to calculate the total number of elements in the ndarray based on its shape
int ft_calculate_total_elements(int *shape, int ndim) {
    int total = 1;
    for (int i = 0; i < ndim; i++) {
        total *= shape[i];
    }
    return total;
}

// Broadcast function to make the shapes compatible
int *ft_ndarray_broadcast(ndarray *a, ndarray *b) {
    int max_ndim = a->ndim > b->ndim ? a->ndim : b->ndim;
    
    // Pad the smaller array's shape with ones
    int *a_shape_padded = (int*) ft_malloc(max_ndim * sizeof(int));
    int *b_shape_padded = (int*) ft_malloc(max_ndim * sizeof(int));

    for (int i = 0; i < max_ndim; i++) {
        if (i < max_ndim - a->ndim) {
            a_shape_padded[i] = 1;
        } else {
            a_shape_padded[i] = a->shape[i - (max_ndim - a->ndim)];
        }

        if (i < max_ndim - b->ndim) {
            b_shape_padded[i] = 1;
        } else {
            b_shape_padded[i] = b->shape[i - (max_ndim - b->ndim)];
        }

        // Check compatibility of shapes
        if (a_shape_padded[i] != b_shape_padded[i] && a_shape_padded[i] != 1 && b_shape_padded[i] != 1) {
            ft_printf("Broadcasting error: Shapes are not compatible\n");
            ft_free(a_shape_padded);
            ft_free(b_shape_padded);
            return NULL;
        }
    }

    // After broadcasting, both arrays should have the same shape
    return a_shape_padded;
}

// Function to add two ndarrays (broadcasting supported)
ndarray *ft_ndarray_add(ndarray *a, ndarray *b) {
    // Ensure that the shapes are broadcast-compatible
    int *broadcast_shape = ft_ndarray_broadcast(a, b);
    if (broadcast_shape == NULL) {
        return NULL;
    }

    int total_elements = ft_calculate_total_elements(broadcast_shape, a->ndim > b->ndim ? a->ndim : b->ndim);
    
    // Allocate new ndarray for the result
    ndarray *result = (ndarray*) ft_malloc(sizeof(ndarray));
    result->shape = broadcast_shape;
    result->ndim = a->ndim > b->ndim ? a->ndim : b->ndim;
    result->itemsize = a->itemsize;

    // Allocate data for the result
    result->data = ft_malloc(total_elements * result->itemsize);

    // Perform element-wise addition with broadcasting
    for (int i = 0; i < total_elements; i++) {
        if (a->itemsize == sizeof(int)) {
            int *a_data = (int*) a->data;
            int *b_data = (int*) b->data;
            int *result_data = (int*) result->data;
            result_data[i] = a_data[i % ft_calculate_total_elements(a->shape, a->ndim)] +
                             b_data[i % ft_calculate_total_elements(b->shape, b->ndim)];
        }
        else if (a->itemsize == sizeof(float)) {
            float *a_data = (float*) a->data;
            float *b_data = (float*) b->data;
            float *result_data = (float*) result->data;
            result_data[i] = a_data[i % ft_calculate_total_elements(a->shape, a->ndim)] +
                             b_data[i % ft_calculate_total_elements(b->shape, b->ndim)];
        }
        else if (a->itemsize == sizeof(double)) {
            double *a_data = (double*) a->data;
            double *b_data = (double*) b->data;
            double *result_data = (double*) result->data;
            result_data[i] = a_data[i % ft_calculate_total_elements(a->shape, a->ndim)] +
                             b_data[i % ft_calculate_total_elements(b->shape, b->ndim)];
        }
    }

    return result;
}

// // Helper function to print ndarray
// void ft_print_ndarray(ndarray *arr) {
//     int total_elements = ft_calculate_total_elements(arr->shape, arr->ndim);

//     if (arr->itemsize == sizeof(int)) {
//         int *data = (int*) arr->data;
//         for (int i = 0; i < total_elements; i++) {
//             ft_printf("%d ", data[i]);
//         }
//     }
//     else if (arr->itemsize == sizeof(float)) {
//         float *data = (float*) arr->data;
//         for (int i = 0; i < total_elements; i++) {
//             ft_printf("%f ", data[i]);
//         }
//     }
//     else if (arr->itemsize == sizeof(double)) {
//         double *data = (double*) arr->data;
//         for (int i = 0; i < total_elements; i++) {
//             ft_printf("%lf ", data[i]);
//         }
//     }
//     ft_printf("\n");
// }