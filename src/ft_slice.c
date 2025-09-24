#include "ft_mini_numpy.h"

t_slice ft_ndarray_slice(float *matrix, int total_cols, int start_row, int start_col, int num_rows, int num_cols) {
    t_slice s;
    s.data = &matrix[start_row * total_cols + start_col];
    s.rows = num_rows;
    s.cols = num_cols;
    s.stride = total_cols;
    return s;
}

float ft_slice_get(t_slice *s, int row, int col) {
    return s->data[row * s->stride + col];
}

ndarray_view ft_slice_ndarray(ndarray *arr, int start[], int end[]) {
    ndarray_view view;
    view.ndim = arr->ndim;
    view.itemsize = arr->itemsize;

    // Allocate shape and strides
    view.shape = (int *)ft_malloc(sizeof(int) * view.ndim);
    view.strides = (int *)ft_malloc(sizeof(int) * view.ndim);

    // Calculate shape and strides
    size_t offset = 0;
    for (int i = 0; i < view.ndim; i++) {
        view.shape[i] = end[i] - start[i];
        view.strides[i] = arr->itemsize;
        for (int j = i + 1; j < view.ndim; j++) {
            view.strides[i] *= arr->shape[j];
        }
        offset += start[i] * view.strides[i];
    }

    view.data = (char *)arr->data + offset;
    return view;
}

ndarray* ft_ndarray_1d_slice(ndarray *arr, int start, int end) {
    int new_shape[1] = {end - start};
    ndarray *slice = ft_create_ndarray_with_strides(new_shape, 1, arr->itemsize);

    int total_elements = new_shape[0];
    for (int i = 0; i < total_elements; i++) {
        ft_memcpy((char*)slice->data + i * arr->itemsize,
               (char*)arr->data + (start + i) * arr->itemsize,
               arr->itemsize);
    }

    return slice;
}

void *ft_ndarray_view_get(const ndarray_view *view, int row, int col) {
    return (char*)view->data + row * view->strides[0] + col * view->strides[1];
}

void *ft_get_view_element(ndarray_view *view, int indices[]) {
    size_t offset = 0;
    for (int i = 0; i < view->ndim; i++) {
        offset += indices[i] * view->strides[i];
    }
    return (char *)view->data + offset;
}

ndarray_view *ft_create_view(ndarray *original, int *start, int *end) {
    if (!original || !start || !end) return NULL;

    int ndim = original->ndim;
    int *new_shape = (int *)ft_malloc(sizeof(int) * ndim);
    int *strides = (int *)ft_malloc(sizeof(int) * ndim);

    if (!new_shape || !strides) return NULL;

    size_t stride = original->itemsize;
    for (int i = ndim - 1; i >= 0; i--) {
        strides[i] = stride;
        stride *= original->shape[i];
    }

    size_t offset = 0;
    for (int i = 0; i < ndim; i++) {
        if (start[i] < 0 || end[i] > original->shape[i] || start[i] >= end[i]) {
            ft_free(new_shape);
            ft_free(strides);
            return NULL;
        }
        new_shape[i] = end[i] - start[i];
        offset += start[i] * strides[i];
    }

    ndarray_view *view = (ndarray_view *)ft_malloc(sizeof(ndarray_view));
    view->data = (void *)((char *)original->data + offset);
    view->shape = new_shape;
    view->ndim = ndim;
    view->itemsize = original->itemsize;
    view->strides = strides;

    return view;
}


void *ft_get_from_view(ndarray_view *view, int *indices) {
    char *data_ptr = (char *)view->data;
    size_t offset = 0;
    for (int i = 0; i < view->ndim; i++) {
        offset += indices[i] * view->strides[i];
    }
    return (void *)(data_ptr + offset);
}

void ft_free_view(ndarray_view *view) {
    if (!view) return;
    ft_free(view->shape);
    ft_free(view->strides);
    ft_free(view);
}

void ft_print_view(ndarray_view *view, char type) {
    if (!view) return;
    int total = 1;
    for (int i = 0; i < view->ndim; i++)
        total *= view->shape[i];

    printf("View: [ ");
    for (int i = 0; i < total; i++) {
        char *ptr = (char *)view->data;
        if (type == 'i') {
            int val;
            ft_memcpy(&val, ptr + i * view->itemsize, view->itemsize);
            printf("%d ", val);
        } else if (type == 'f') {
            float val;
            ft_memcpy(&val, ptr + i * view->itemsize, view->itemsize);
            printf("%.2f ", val);
        }
    }
    printf("]\n");
}