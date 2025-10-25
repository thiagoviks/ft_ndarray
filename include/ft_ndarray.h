#ifndef FT_NDARRAY_H
#define FT_NDARRAY_H

#include <ft_maki.h>

typedef struct {
  void *data;         // Pointer to raw data
  int *shape;         // Array dimensions
  int ndim;           // Number of dimensions
  ft_size_t itemsize; // Size of each element (e.g., sizeof(int))
  int *strides;       // Strides for each dimension
} ndarray;

typedef struct {
  void *data;
  int *shape;
  int ndim;
  ft_size_t itemsize;
  int *strides; // how many bytes to skip for each dimension
} ndarray_view;

typedef struct {
  float *data;
  int rows;
  int cols;
  int stride; // how many elements to skip to go to the next row
} t_slice;

t_slice ft_ndarray_slice(float *matrix, int total_cols, int start_row,
                         int start_col, int num_rows, int num_cols);
float ft_slice_get(t_slice *s, int row, int col);

// Function prototypes
ndarray *ft_create_ndarray(int *shape, int ndim, ft_size_t itemsize);
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
// More Slice API
double ft_ndarray_sum(ndarray *arr);
double ft_ndarray_mean(ndarray *arr);
ndarray *ft_ndarray_1d_slice(ndarray *arr, int start, int end);
ndarray *ft_ndarray_add(ndarray *a, ndarray *b);
int *ft_ndarray_broadcast(ndarray *a, ndarray *b);
int ft_calculate_total_elements(int *shape, int ndim);
ndarray *ft_create_ndarray_with_strides(int *shape, int ndim,
                                        ft_size_t itemsize);

// New slicing functions
void *ft_get_from_view(ndarray_view *view, int *indices);
ndarray_view ft_slice_ndarray(ndarray *arr, int start[], int end[]);
void *ndarray_view_get(const ndarray_view *view, int row, int col);
void *ft_get_view_element(ndarray_view *view, int indices[]);

// Pandas like functions

#ifndef FT_NAN
#define FT_NAN (0.0 / 0.0)
#endif

typedef struct {
  char *name;
  ndarray *data; // each column is an independent ndarray
  char type;     // 'i' = int, 'f' = double, 's' = string
} df_column;

typedef struct {
  df_column *columns;
  int ncols;
  int nrows;
} dataframe;

typedef double (*apply_func)(double);
// for data numbers(int, float, double)
typedef void (*apply_func_numeric)(void *element, ft_size_t itemsize);
// for strings (char*)
typedef void (*apply_func_string)(char **element);

double ft_ndarray_get(const ndarray *arr, int row, int col);
void ft_ndarray_head(const ndarray *arr, int n);
void ft_ndarray_tail(const ndarray *arr, int n);
void ft_ndarray_describe(const ndarray *arr);
void ft_ndarray_sum_per_colunm(const ndarray *arr);
void ft_ndarray_isnan(const ndarray *arr);
void ft_ndarray_fillna(ndarray *arr, double value);
void ft_ndarray_sort(ndarray *arr, int column);
void ft_ndarray_groupby_sum(const ndarray *arr, int group_col);
void ft_ndarray_apply(ndarray *arr, apply_func func);
void ft_ndarray_apply_numeric(ndarray *arr, apply_func_numeric func);
void ft_ndarray_apply_string(ndarray *arr, apply_func_string func);
double ft_ndarray_square(double x);
void ft_ndarray_square_num(void *element, ft_size_t itemsize);
void ft_ndarray_increment_num(void *element, ft_size_t itemsize);
void ft_ndarray_strtoupper(char **element);
void ft_ndarray_strtolower(char **element);
void ft_ndarray_fillna_string(char **element);

ndarray ft_ndarray_read_csv(const char *filename);
void ft_ndarray_info(const ndarray *arr);
ndarray *ft_ndarray_column(const ndarray *arr, int column);
void ft_ndarray_drop(ndarray *arr, int index, int axis);
ndarray *ft_ndarray_loc(const ndarray *arr, int label);
ndarray *ft_ndarray_iloc(const ndarray *arr, int index);

dataframe *df_create(char **col_names, char *types, int ncols, int nrows);
void df_print(dataframe *df);
void df_free(dataframe *df);
#endif
