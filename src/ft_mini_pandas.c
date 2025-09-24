
#include <math.h>
#include <ft_maki.h>
#include "../include/ft_mini_pandas.h"

double ft_ndarray_get(const ndarray *arr, int row, int col);

double ft_ndarray_get(const ndarray *arr, int row, int col) {
    char *base = (char*)arr->data;
    size_t offset = row * arr->strides[0] + col * arr->strides[1];
    return *(double*)(base + offset);
}


void ft_ndarray_head(const ndarray *arr, int n) {
    int rows = arr->shape[0];
    int cols = arr->shape[1];
    int count = n < rows ? n : rows;
    double *data = (double *)arr->data;

    for (int i = 0; i < count; i++) {
        for (int j = 0; j < cols; j++) {
            ft_printf("%.2f ", data[i * cols + j]);
        }
        ft_printf("\n");
    }
}

void ft_ndarray_tail(const ndarray *arr, int n) {
    int rows = arr->shape[0];
    int cols = arr->shape[1];
    int start = rows - n;
    if (start < 0) start = 0;
    double *data = (double *)arr->data;

    for (int i = start; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            ft_printf("%.2f ", data[i * cols + j]);
        }
        ft_printf("\n");
    }
}

void ft_ndarray_describe(const ndarray *arr) {
    int rows = arr->shape[0];
    int cols = arr->shape[1];
    double *data = (double *)arr->data;

    for (int j = 0; j < cols; j++) {
        double sum = 0, min = data[j], max = data[j];
        for (int i = 0; i < rows; i++) {
            //double val = data[i * cols + j];
            double val = ft_ndarray_get(arr, i, cols);
            if(!ft_isnan(val))
            {
                if (val < min) min = val;
                if (val > max) max = val;
                sum += val;
            }
        }
        ft_printf("Col %d => Min: %.2f Max: %.2f Mean: %.2f\n", j, min, max, sum / rows);
    }
}

void ft_ndarray_sum_per_colunm(const ndarray *arr) {
    int rows = arr->shape[0];
    int cols = arr->shape[1];
    double *data = (double *)arr->data;

    for (int j = 0; j < cols; j++) {
        double sum = 0;
        for (int i = 0; i < rows; i++) {
            sum += data[i * cols + j];
        }
        ft_printf("Sum of Col %d: %.2f\n", j, sum);
    }
}

void ft_ndarray_isnan(const ndarray *arr) {
    int total = 1;
    for (int i = 0; i < arr->ndim; i++) total *= arr->shape[i];
    double *data = (double *)arr->data;

    for (int i = 0; i < total; i++) {
        if (ft_isnan(data[i])) {
            ft_printf("NaN at index %d\n", i);
        }
    }
}

void ft_ndarray_fillna(ndarray *arr, double value) {
    int total = 1;
    for (int i = 0; i < arr->ndim; i++) total *= arr->shape[i];
    double *data = (double *)arr->data;

    for (int i = 0; i < total; i++) {
        if (ft_isnan(data[i])) {
            data[i] = value;
        }
    }
}

void ft_ndarray_sort(ndarray *arr, int column) {
    int rows = arr->shape[0];
    int cols = arr->shape[1];
    double *data = (double *)arr->data;

    for (int i = 0; i < rows - 1; i++) {
        for (int j = i + 1; j < rows; j++) {
            if (data[i * cols + column] > data[j * cols + column]) {
                for (int k = 0; k < cols; k++) {
                    double temp = data[i * cols + k];
                    data[i * cols + k] = data[j * cols + k];
                    data[j * cols + k] = temp;
                }
            }
        }
    }
}

void ft_ndarray_groupby_sum(const ndarray *arr, int group_col) {
    int rows = arr->shape[0];
    int cols = arr->shape[1];
    double *data = (double *)arr->data;

    ft_printf("Group By Column %d and Sum:\n", group_col);
    for (int i = 0; i < rows; i++) {
        double key = data[i * cols + group_col];
        double sum = 0;
        for (int j = 0; j < rows; j++) {
            if (data[j * cols + group_col] == key) {
                sum += data[j * cols + group_col];
            }
        }
        ft_printf("Group %.2f => Sum: %.2f\n", key, sum);
    }
}

void ft_ndarray_apply(ndarray *arr, apply_func func) {
    int total = 1;
    for (int i = 0; i < arr->ndim; i++) total *= arr->shape[i];
    double *data = (double *)arr->data;

    for (int i = 0; i < total; i++) {
        data[i] = func(data[i]);
    }
}

double ft_square(double x) {
    return x * x;
}

// ndarray_pandas.c


// Function to read a CSV file and convert it to ndarray
ndarray ft_ndarray_read_csv(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        ft_exit(EXIT_FAILURE);
    }

    char line[1024];
    int rows = 0, cols = 0;

    // Count number of rows and columns
    while (fgets(line, sizeof(line), file)) {
        rows++;
        char *token = ft_strtok(line, ",");
        int col_count = 0;
        while (token) {
            col_count++;
            token = ft_strtok(NULL, ",");
        }
        if (cols == 0) {
            cols = col_count;
        }
    }

    fseek(file, 0, SEEK_SET);

    double *data = (double *)ft_malloc(rows * cols * sizeof(double));
    int *shape = (int *)ft_malloc(2 * sizeof(int));
    int *strides = (int *)ft_malloc(2 * sizeof(int));
    shape[0] = rows;
    shape[1] = cols;
    strides[0] = cols * sizeof(double);
    strides[1] = sizeof(double);

    int index = 0;
    while (fgets(line, sizeof(line), file)) {
        char *token = ft_strtok(line, ",");
        while (token) {
            data[index++] = ft_atof(token);
            token = ft_strtok(NULL, ",");
        }
    }

    fclose(file);

    ndarray arr = {data, shape, 2, sizeof(double), strides};
    return arr;
}

// Function to print shape, dtype and non-null count
void ft_ndarray_info(const ndarray *arr) {
    ft_printf("Shape: (%d, %d)\n", arr->shape[0], arr->shape[1]);
    ft_printf("Data type: %.0zu bytes per element\n", arr->itemsize);

    int non_null_count = 0;
    for (int i = 0; i < arr->shape[0]; i++) {
        for (int j = 0; j < arr->shape[1]; j++) {
            double *elem = (double *)arr->data + i * arr->strides[0] / arr->itemsize + j * arr->strides[1] / arr->itemsize;
            if (*elem != NAN) {
                non_null_count++;
            }
        }
    }
    ft_printf("Non-null values: %d\n", non_null_count);
}

// Function to access a specific column
ndarray *ft_ndarray_column(const ndarray *arr, int column) {
    int rows = arr->shape[0];
    double *column_data = (double *)ft_malloc(rows * sizeof(double));

    for (int i = 0; i < rows; i++) {
        column_data[i] = *((double *)arr->data + i * arr->strides[0] / arr->itemsize + column * arr->strides[1] / arr->itemsize);
    }

    int *shape = (int *)ft_malloc(1 * sizeof(int));
    shape[0] = rows;
    int *strides = (int *)ft_malloc(1 * sizeof(int));
    strides[0] = sizeof(double);

    ndarray *col = (ndarray *)ft_malloc(sizeof(ndarray));
    col->data = column_data;
    col->shape = shape;
    col->ndim = 1;
    col->itemsize = sizeof(double);
    col->strides = strides;

    return col;
}

// Function to drop rows or columns
void ft_ndarray_drop(ndarray *arr, int index, int axis) {
    if (axis == 0) {
        // Drop row
        int rows = arr->shape[0];
        double *data = (double *)ft_malloc((rows - 1) * arr->shape[1] * sizeof(double));
        int index_data = 0;
        for (int i = 0; i < rows; i++) {
            if (i != index) {
                for (int j = 0; j < arr->shape[1]; j++) {
                    data[index_data++] = *((double *)arr->data + i * arr->strides[0] / arr->itemsize + j * arr->strides[1] / arr->itemsize);
                }
            }
        }
        arr->data = data;
        arr->shape[0] -= 1;
    }
    // Implement column drop similarly
}

// Function to access a row by label
ndarray *ft_ndarray_loc(const ndarray *arr, int label) {
    double *row_data = (double *)ft_malloc(arr->shape[1] * sizeof(double));

    for (int i = 0; i < arr->shape[1]; i++) {
        row_data[i] = *((double *)arr->data + label * arr->strides[0] / arr->itemsize + i * arr->strides[1] / arr->itemsize);
    }

    int *shape = (int *)ft_malloc(1 * sizeof(int));
    shape[0] = arr->shape[1];
    int *strides = (int *)ft_malloc(1 * sizeof(int));
    strides[0] = sizeof(double);

    ndarray *row = (ndarray *)ft_malloc(sizeof(ndarray));
    row->data = row_data;
    row->shape = shape;
    row->ndim = 1;
    row->itemsize = sizeof(double);
    row->strides = strides;

    return row;
}

// Function to access a row by index
ndarray *ft_ndarray_iloc(const ndarray *arr, int index) {
    return ft_ndarray_loc(arr, index);
}
