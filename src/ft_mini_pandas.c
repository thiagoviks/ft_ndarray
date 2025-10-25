#include "../include/ft_mini_pandas.h"
#include <ft_maki.h>

double ft_ndarray_get(const ndarray *arr, int row, int col) {
  char *base = (char *)arr->data;
  ft_size_t offset = row * arr->strides[0] + col * arr->strides[1];
  return (*(double *)(base + offset));
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
  if (start < 0)
    start = 0;
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
      // double val = data[i * cols + j];
      double val = ft_ndarray_get(arr, i, cols);
      if (!ft_isnan(val)) {
        if (val < min)
          min = val;
        if (val > max)
          max = val;
        sum += val;
      }
    }
    ft_printf("Col %d => Min: %.2f Max: %.2f Mean: %.2f\n", j, min, max,
              sum / rows);
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
  for (int i = 0; i < arr->ndim; i++)
    total *= arr->shape[i];
  double *data = (double *)arr->data;

  for (int i = 0; i < total; i++) {
    if (ft_isnan(data[i])) {
      ft_printf("NaN at index %d\n", i);
    }
  }
}

void ft_ndarray_fillna(ndarray *arr, double value) {
  int total = 1;
  for (int i = 0; i < arr->ndim; i++)
    total *= arr->shape[i];
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
  for (int i = 0; i < arr->ndim; i++)
    total *= arr->shape[i];

  if (arr->itemsize != sizeof(double)) {
    ft_fprintf(ft_stderr,
               "ft_ndarray_apply: itemsize incompatível (esperado double)\n");
    return;
  }
  double *data = (double *)arr->data;

  for (int i = 0; i < total; i++) {
    data[i] = func(data[i]);
  }
}

// Apply numeric function
void ft_ndarray_apply_numeric(ndarray *arr, apply_func_numeric func) {
  int total = 1;
  for (int i = 0; i < arr->ndim; i++)
    total *= arr->shape[i];

  char *data = (char *)arr->data;

  for (int i = 0; i < total; i++) {
    void *element = data + i * arr->itemsize;
    func(element, arr->itemsize);
  }
}

// Apply string function
void ft_ndarray_apply_string(ndarray *arr, apply_func_string func) {
  if (arr->itemsize != sizeof(char *)) {
    ft_fprintf(ft_stderr,
               "ft_apply_string: itemsize inválido (esperado char*)\n");
    return;
  }

  int total = 1;
  for (int i = 0; i < arr->ndim; i++)
    total *= arr->shape[i];

  char **data = (char **)arr->data;

  for (int i = 0; i < total; i++) {
    func(&data[i]); // passa o ponteiro da string
  }
}

double ft_ndarray_square(double x) { return (x * x); }

// Square generic
void ft_ndarray_square_num(void *element, ft_size_t itemsize) {
  if (itemsize == sizeof(int)) {
    int *x = (int *)element;
    *x = (*x) * (*x);
  } else if (itemsize == sizeof(float)) {
    float *x = (float *)element;
    *x = (*x) * (*x);
  } else if (itemsize == sizeof(double)) {
    double *x = (double *)element;
    *x = (*x) * (*x);
  }
}

// Increment +1 generic
void ft_ndarray_increment_num(void *element, ft_size_t itemsize) {
  if (itemsize == sizeof(int)) {
    (*(int *)element)++;
  } else if (itemsize == sizeof(float)) {
    (*(float *)element)++;
  } else if (itemsize == sizeof(double)) {
    (*(double *)element)++;
  }
}

void ft_ndarray_strtoupper(char **element) {
  char *s = *element;
  if (!s)
    return;
  for (int i = 0; s[i]; i++) {
    s[i] = (char)ft_toupper((unsigned char)s[i]);
  }
}

void ft_ndarray_strtolower(char **element) {
  char *s = *element;
  if (!s)
    return;
  for (int i = 0; s[i]; i++) {
    s[i] = (char)ft_tolower((unsigned char)s[i]);
  }
}

void ft_ndarray_fillna_string(char **element) {
  if (!*element) {
    *element = ft_strdup("N/A"); // ou ft_strdup
  }
}

// ndarray_pandas.c

// Function to read a CSV file and convert it to ndarray

// CSV-aware tokenizer (handles quoted fields with commas inside)
static char *ft_csv_next_token(char **line) {
  if (!line || !*line)
    return (FT_NULL);

  char *start = *line;
  char *p = start;
  int in_quotes = 0;

  while (*p) {
    if (*p == '"') {
      in_quotes = !in_quotes; // toggle quote state
    } else if (*p == ',' && !in_quotes) {
      // End of token
      *p = '\0';
      *line = p + 1;
      return (start);
    }
    p++;
  }
  // Last token in the line
  *line = FT_NULL;
  return (start);
}

// Helper: trim spaces and surrounding quotes
static char *ft_csv_clean_field(char *token) {
  if (!token)
    return (FT_NULL);

  // Trim leading spaces
  while (*token == ' ' || *token == '\t' || *token == '\n')
    token++;

  // Trim trailing spaces
  char *end = token + ft_strlen(token) - 1;
  while (end > token && (*end == ' ' || *end == '\t' || *end == '\n'))
    *end-- = '\0';

  // Remove surrounding quotes if present
  if (*token == '"' && end > token && *end == '"') {
    *end = '\0';
    token++;
  }

  return (token);
}

// ndarray ft_ndarray_read_csv(const char *filename) {
//   T_FT_FILE *file = ft_fopen(filename, "r");
//   if (!file) {
//     ft_perror("Error opening file");
//     ft_exit(FT_EXIT_FAILURE);
//   }

//   char line[4096]; // large enough buffer for long rows
//   int rows = 0, cols = 0;

//   // First pass: count rows and validate column count
//   while (ft_fgets(line, sizeof(line), file)) {
//     int col_count = 0;
//     char *cursor = line;
//     char *token = ft_csv_next_token(&cursor);
//     while (token) {
//       col_count++;
//       token = ft_csv_next_token(&cursor);
//     }
//     if (cols == 0) {
//       cols = col_count; // set initial number of columns
//     } else if (col_count != cols) {
//       ft_fprintf(ft_stderr, "Inconsistent number of columns at row %d\n",
//                  rows + 1);
//       ft_exit(FT_EXIT_FAILURE);
//     }
//     rows++;
//   }

//   // Reset file pointer
//   ft_fseek(file, 0, FT_SEEK_SET);

//   // Allocate ndarray memory
//   double *data = (double *)ft_malloc(rows * cols * sizeof(double));
//   int *shape = (int *)ft_malloc(2 * sizeof(int));
//   int *strides = (int *)ft_malloc(2 * sizeof(int));
//   shape[0] = rows;
//   shape[1] = cols;
//   strides[0] = cols * sizeof(double);
//   strides[1] = sizeof(double);

//   // Second pass: read and fill the ndarray
//   int index = 0;
//   while (ft_fgets(line, sizeof(line), file)) {
//     char *cursor = line;
//     char *token = ft_csv_next_token(&cursor);
//     while (token) {
//       char *clean = ft_csv_clean_field(token);
//       data[index++] = ft_atof(clean);
//       token = ft_csv_next_token(&cursor);
//     }
//   }

//   ft_fclose(file);

//   ndarray arr = {data, shape, 2, sizeof(double), strides};
//   return (arr);
// }

// Function to print shape, dtype and non-null count
void ft_ndarray_info(const ndarray *arr) {
  ft_printf("Shape: (%d, %d)\n", arr->shape[0], arr->shape[1]);
  ft_printf("Data type: %.0zu bytes per element\n", arr->itemsize);

  int non_null_count = 0;
  for (int i = 0; i < arr->shape[0]; i++) {
    for (int j = 0; j < arr->shape[1]; j++) {
      double *elem = (double *)arr->data + i * arr->strides[0] / arr->itemsize +
                     j * arr->strides[1] / arr->itemsize;
      if (*elem != FT_NAN) {
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
    column_data[i] =
        *((double *)arr->data + i * arr->strides[0] / arr->itemsize +
          column * arr->strides[1] / arr->itemsize);
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

  return (col);
}

// Function to drop rows or columns
void ft_ndarray_drop(ndarray *arr, int index, int axis) {
  if (axis == 0) {
    // Drop row
    int rows = arr->shape[0];
    double *data =
        (double *)ft_malloc((rows - 1) * arr->shape[1] * sizeof(double));
    int index_data = 0;
    for (int i = 0; i < rows; i++) {
      if (i != index) {
        for (int j = 0; j < arr->shape[1]; j++) {
          data[index_data++] =
              *((double *)arr->data + i * arr->strides[0] / arr->itemsize +
                j * arr->strides[1] / arr->itemsize);
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
    row_data[i] =
        *((double *)arr->data + label * arr->strides[0] / arr->itemsize +
          i * arr->strides[1] / arr->itemsize);
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

  return (row);
}

// Function to access a row by index
ndarray *ft_ndarray_iloc(const ndarray *arr, int index) {
  return (ft_ndarray_loc(arr, index));
}

dataframe *df_create(char **col_names, char *types, int ncols, int nrows) {
  dataframe *df = ft_malloc(sizeof(dataframe));
  df->ncols = ncols;
  df->nrows = nrows;
  df->columns = ft_malloc(sizeof(df_column) * ncols);

  for (int i = 0; i < ncols; i++) {
    int shape[1] = {nrows};
    df->columns[i].name = ft_strdup(col_names[i]);
    df->columns[i].type = types[i];

    ft_size_t itemsize = (types[i] == 'i') ? sizeof(int)
                         : (types[i] == 'f')
                             ? sizeof(double)
                             : sizeof(char *); // string = pointer
    df->columns[i].data = ft_create_ndarray(shape, 1, itemsize);
  }
  return (df);
}

// Print the DataFrame
void df_print(dataframe *df) {
  // Header
  for (int c = 0; c < df->ncols; c++) {
    ft_printf("%-10s ", df->columns[c].name);
  }
  ft_printf("\n");

  // Lines
  for (int r = 0; r < df->nrows; r++) {
    for (int c = 0; c < df->ncols; c++) {
      df_column col = df->columns[c];
      if (col.type == 'i') {
        int val = ((int *)col.data->data)[r];
        ft_printf("%-10d ", val);
      } else if (col.type == 'f') {
        double val = ((double *)col.data->data)[r];
        ft_printf("%-10.2f ", val);
      } else if (col.type == 's') {
        char *val = ((char **)col.data->data)[r];
        ft_printf("%-10s ", val);
      }
    }
    ft_printf("\n");
  }
}

// Frees DataFrame memory
void df_free(dataframe *df) {
  for (int i = 0; i < df->ncols; i++) {
    ft_free(df->columns[i].name);
    ft_free_ndarray(df->columns[i].data);
  }
  ft_free(df->columns);
  ft_free(df);
}
