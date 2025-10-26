# ft_ndarray

A C library for N-dimensional array operations with pandas-like functionality, built as part of the ft_maki project.

**Note**: This is a learning project inspired by NumPy and pandas functionality.

## Overview

ft_ndarray provides a lightweight, NumPy-inspired interface for working with multi-dimensional arrays in C, along with data manipulation functions similar to pandas DataFrames.

### Installation
```bash
git clone https://github.com/thiagoviks/ft_ndarray.git
cd ft_ndarray
sudo make install
```

## Features

### Core Array Operations
- **N-dimensional arrays**: Create and manipulate arrays with arbitrary dimensions
- **Memory-efficient views**: Work with array slices without copying data
- **Broadcasting**: Automatic shape alignment for operations
- **Linear algebra**: Matrix operations, transpose, dot product

### Data Analysis Tools
- **Statistical functions**: Sum, mean, describe
- **Data inspection**: head, tail, info
- **Data cleaning**: fillna, isnan handling
- **Sorting and grouping**: Sort by column, groupby operations
- **Apply functions**: Transform data with custom functions

### DataFrame Support
- **Structured data**: Work with heterogeneous columns (int, float, string)
- **CSV I/O**: Read data from CSV files
- **Indexing**: loc and iloc for label and integer-based indexing
- **Column operations**: Select, drop, and manipulate columns

## Data Structures

### `ndarray`
```c
typedef struct {
  void *data;         // Pointer to raw data
  int *shape;         // Array dimensions
  int ndim;           // Number of dimensions
  ft_size_t itemsize; // Size of each element
  int *strides;       // Strides for each dimension
} ndarray;
```

### `dataframe`
```c
typedef struct {
  df_column *columns;
  int ncols;
  int nrows;
} dataframe;
```

### `ndarray_view`
Memory-efficient view into existing arrays without copying data.

## Core Functions

### Array Creation & Memory
```c
ndarray *ft_create_ndarray(int *shape, int ndim, ft_size_t itemsize);
void ft_free_ndarray(ndarray *arr);
ndarray_view *ft_create_view(ndarray *original, int *start, int *shape);
```

### Mathematical Operations
```c
void ft_add_ndarrays(ndarray *a, ndarray *b, ndarray *result);
void ft_scalar_multiply(ndarray *a, double scalar);
double ft_dot_product(ndarray *a, ndarray *b);
ndarray *ft_ndarray_2d_transpose(ndarray *a);
```

### Statistics & Analysis
```c
double ft_ndarray_sum(ndarray *arr);
double ft_ndarray_mean(ndarray *arr);
void ft_ndarray_describe(const ndarray *arr);
void ft_ndarray_groupby_sum(const ndarray *arr, int group_col);
```

### Data Manipulation
```c
void ft_ndarray_head(const ndarray *arr, int n);
void ft_ndarray_tail(const ndarray *arr, int n);
void ft_ndarray_fillna(ndarray *arr, double value);
void ft_ndarray_sort(ndarray *arr, int column);
```

### Slicing & Indexing
```c
ndarray *ft_ndarray_1d_slice(ndarray *arr, int start, int end);
ndarray_view ft_slice_ndarray(ndarray *arr, int start[], int end[]);
void *ft_get_view_element(ndarray_view *view, int indices[]);
```

### Apply Functions
```c
void ft_ndarray_apply(ndarray *arr, apply_func func);
void ft_ndarray_apply_numeric(ndarray *arr, apply_func_numeric func);
void ft_ndarray_apply_string(ndarray *arr, apply_func_string func);
```

Built-in transformation functions:
- `ft_ndarray_square` / `ft_ndarray_square_num`
- `ft_ndarray_increment_num`
- `ft_ndarray_strtoupper` / `ft_ndarray_strtolower`

### DataFrame Operations
```c
dataframe *df_create(char **col_names, char *types, int ncols, int nrows);
void df_print(dataframe *df);
void df_free(dataframe *df);
ndarray ft_ndarray_read_csv(const char *filename);
```

### Column Operations
```c
ndarray *ft_ndarray_column(const ndarray *arr, int column);
void ft_ndarray_drop(ndarray *arr, int index, int axis);
ndarray *ft_ndarray_loc(const ndarray *arr, int label);
ndarray *ft_ndarray_iloc(const ndarray *arr, int index);
```

## Usage Example

```c
#include <ft_ndarray.h>

double square(double x) { return x * x; }

int main() {
  int shape[2] = {5, 3};
  int strides[2] = {3 * sizeof(double), sizeof(double)};
  double data[15] = {1.0, 2.0,  3.0,  4.0,  FT_NAN, 6.0,  7.0, 8.0,
                     9.0, 10.0, 11.0, 12.0, 13.0,   14.0, 15.0};

  ndarray arr = {.data = data,
                 .shape = shape,
                 .ndim = 2,
                 .itemsize = sizeof(double),
                 .strides = strides};

  ft_ndarray_head(&arr, 3);
  ft_ndarray_describe(&arr);
  ft_ndarray_sum(&arr);
  ft_ndarray_isnan(&arr);
  ft_ndarray_fillna(&arr, 0.0);
  ft_ndarray_sort(&arr, 1);
  ft_ndarray_groupby_sum(&arr, 0);

  ft_ndarray_apply(&arr, square);
  ft_print_ndarray(&arr, 'd');
  return (0);
}
```

**Compile:**
```bash
clang hello.c -o hello -lft_maki -lft_ndarray
./hello
```

## Type Support

- **Numeric types**: `int`, `float`, `double`
- **String type**: `char*`
- Type indicator: `'i'` (int), `'f'` (double), `'s'` (string)

## Building

This library requires the ft_maki project. Include the header in your project:

```c
#include <ft_maki.h>
```

**Platform requirement**: Linux only

This library requires the ft_maki project and is designed for Linux systems.
```bash
# Make sure you're on Linux
clang your_program.c -o your_program  -lft_maki -lft_ndarray
```

## License
MIT

---

## Author
**Maki** - Inspired by Python Pandas, built from scratch in C.
