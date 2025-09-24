#include "ft_mini_numpy.h"
#include <ft_maki.h>

typedef double  (*apply_func)(double);
// for data numbers(int, float, double)
typedef void (*apply_func_numeric)(void *element, size_t itemsize);
// for strings (char*)
typedef void (*apply_func_string)(char **element);

double  ft_ndarray_get(const ndarray *arr, int row, int col);
void    ft_ndarray_head(const ndarray *arr, int n);
void    ft_ndarray_tail(const ndarray *arr, int n);
void    ft_ndarray_describe(const ndarray *arr);
void    ft_ndarray_sum_per_colunm(const ndarray *arr);
void    ft_ndarray_isnan(const ndarray *arr);
void    ft_ndarray_fillna(ndarray *arr, double value);
void    ft_ndarray_sort(ndarray *arr, int column);
void    ft_ndarray_groupby_sum(const ndarray *arr, int group_col);
void    ft_ndarray_apply(ndarray *arr, apply_func func);
void    ft_ndarray_apply_numeric(ndarray *arr, apply_func_numeric func);
void    ft_ndarray_apply_string(ndarray *arr, apply_func_string func);
double  ft_ndarray_square(double x);
void    ft_ndarray_square_num(void *element, size_t itemsize);
void    ft_ndarray_increment_num(void *element, size_t itemsize);

ndarray ft_ndarray_read_csv(const char *filename);
void    ft_ndarray_info(const ndarray *arr);
ndarray *ft_ndarray_column(const ndarray *arr, int column);
void    ft_ndarray_drop(ndarray *arr, int index, int axis);
ndarray *ft_ndarray_loc(const ndarray *arr, int label);
ndarray *ft_ndarray_iloc(const ndarray *arr, int index);

//for internal use of ft_ndarray_describe
//double ft_ndarray_get(const ndarray *arr, int row, int col);