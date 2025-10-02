#ifndef FT_MINI_NUMPY_H
#define FT_MINI_NUMPY_H

#include <stdlib.h>
#include <stdio.h>
#include <ft_maki.h>

typedef struct {
    void *data;        // Pointer to raw data
    int *shape;        // Array dimensions
    int ndim;          // Number of dimensions
    size_t itemsize;   // Size of each element (e.g., sizeof(int))
    int *strides;      // Strides for each dimension
} ndarray;

typedef struct {
    void *data;
    int *shape;
    int ndim;
    size_t itemsize;
    int *strides; // how many bytes to skip for each dimension
} ndarray_view;


typedef struct {
    float *data;
    int rows;
    int cols;
    int stride; // how many elements to skip to go to the next row
} t_slice;

t_slice ft_ndarray_slice(float *matrix, int total_cols, int start_row, int start_col, int num_rows, int num_cols);
float ft_slice_get(t_slice *s, int row, int col);

// Function prototypes
ndarray *ft_create_ndarray(int *shape, int ndim, size_t itemsize);
void ft_free_ndarray(ndarray *arr);
void ft_print_ndarray(ndarray *arr, char type); // Debugging helper
void ft_add_ndarrays(ndarray *a, ndarray *b, ndarray *result);
void ft_scalar_multiply(ndarray *a, double scalar);
double ft_dot_product(ndarray *a, ndarray *b);
ndarray *ft_ndarray_2d_transpose(ndarray *a);

// Slice API
ndarray_view *ft_create_view(ndarray *original, int *start, int *shape);
void ft_free_view(ndarray_view *view);
void ft_print_view(ndarray_view *view, char type);
//More Slice API
double ft_ndarray_sum(ndarray *arr);
double ft_ndarray_mean(ndarray *arr);
ndarray* ft_ndarray_1d_slice(ndarray *arr, int start, int end);
ndarray *ft_ndarray_add(ndarray *a, ndarray *b);
int *ft_ndarray_broadcast(ndarray *a, ndarray *b);
int ft_calculate_total_elements(int *shape, int ndim);
ndarray* ft_create_ndarray_with_strides(int *shape, int ndim, size_t itemsize);
void ft_memory_pool_free();
void *ft_memory_pool_alloc(size_t size);

// New slicing functions
void *ft_get_from_view(ndarray_view *view, int *indices);
ndarray_view ft_slice_ndarray(ndarray *arr, int start[], int end[]);
void *ndarray_view_get(const ndarray_view *view, int row, int col);
void *ft_get_view_element(ndarray_view *view, int indices[]);

#endif
