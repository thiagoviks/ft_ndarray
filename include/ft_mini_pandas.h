#include "ft_mini_numpy.h"

typedef double (*apply_func)(double);

void ft_ndarray_head(const ndarray *arr, int n);
void ft_ndarray_tail(const ndarray *arr, int n);
void ft_ndarray_describe(const ndarray *arr);
void ft_ndarray_sum_per_colunm(const ndarray *arr);
void ft_ndarray_isnan(const ndarray *arr);
void ft_ndarray_fillna(ndarray *arr, double value);
void ft_ndarray_sort(ndarray *arr, int column);
void ft_ndarray_groupby_sum(const ndarray *arr, int group_col);
void ft_ndarray_apply(ndarray *arr, apply_func func);
double ft_square(double x);

ndarray ft_ndarray_read_csv(const char *filename);
void ft_ndarray_info(const ndarray *arr);
ndarray *ft_ndarray_column(const ndarray *arr, int column);
void ft_ndarray_drop(ndarray *arr, int index, int axis);
ndarray *ft_ndarray_loc(const ndarray *arr, int label);
ndarray *ft_ndarray_iloc(const ndarray *arr, int index);