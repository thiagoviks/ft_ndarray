#include "include/ft_mini_numpy.h"
#include "include/ft_mini_pandas.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ft_maki.h>

int main() {
//     // Define shapes
//     int shape2D[2] = {2, 3};
//     int shape1D[1] = {3};

//     // Create 2D ndarrays
//     ndarray *arr1 = ft_create_ndarray(shape2D, 2, sizeof(int));
//     ndarray *arr2 = ft_create_ndarray(shape2D, 2, sizeof(int));
//     ndarray *result = ft_create_ndarray(shape2D, 2, sizeof(int));

//     // Initialize 2D arrays
//     int *data1 = (int *)arr1->data;
//     int *data2 = (int *)arr2->data;
//     for (int i = 0; i < 6; i++) {
//         data1[i] = i;
//         data2[i] = i * 2;
//     }

//     // Print initial arrays
//     printf("Array 1: ");
//     ft_print_ndarray(arr1, 'i');
//     printf("Array 2: ");
//     ft_print_ndarray(arr2, 'i');

//     // Perform element-wise addition
//     ft_add_ndarrays(arr1, arr2, result);
//     printf("Sum: ");
//     ft_print_ndarray(result, 'i');

//     // Perform scalar multiplication
//     ft_scalar_multiply(arr1, 2.5);
//     printf("Array 1 after scalar multiplication: ");
//     ft_print_ndarray(arr1, 'i');

//     // Free 2D arrays
//     ft_free_ndarray(arr1);
//     ft_free_ndarray(arr2);
//     ft_free_ndarray(result);

//     // Create and initialize 1D arrays for dot product
//     ndarray *vec1 = ft_create_ndarray(shape1D, 1, sizeof(int));
//     ndarray *vec2 = ft_create_ndarray(shape1D, 1, sizeof(int));

//     int values1[] = {1, 2, 3};
//     int values2[] = {4, 5, 6};
//     ft_memcpy(vec1->data, values1, sizeof(values1));
//     ft_memcpy(vec2->data, values2, sizeof(values2));

//     // Compute and print dot product
//     printf("Dot product: %.2f\n", ft_dot_product(vec1, vec2));

//     // Create and initialize 2D matrix for transpose
//     ndarray *matrix = ft_create_ndarray(shape2D, 2, sizeof(int));
//     int valuesMatrix[] = {1, 2, 3, 4, 5, 6};
//     ft_memcpy(matrix->data, valuesMatrix, sizeof(valuesMatrix));

//     printf("Original matrix:\n");
//     ft_print_ndarray(matrix, 'i');

//     // Compute and print transposed matrix
//     ndarray *transposed = ft_ndarray_2d_transpose(matrix);
//     printf("Transposed matrix:\n");
//     ft_print_ndarray(transposed, 'i');

//     // Free remaining arrays
//     ft_free_ndarray(vec1);
//     ft_free_ndarray(vec2);
//     ft_free_ndarray(matrix);
//     ft_free_ndarray(transposed);

//     float f_matrix[3][4] = {
//         {1, 2, 3, 4},
//         {5, 6, 7, 8},
//         {9, 10, 11, 12}
//     };

//     t_slice s = ft_ndarray_slice(&f_matrix[0][0], 4, 1, 1, 2, 2);
//     printf("Sliced matrix:\n");
//     for (int i = 0; i < s.rows; i++) {
//         for (int j = 0; j < s.cols; j++) {
//             printf("%.0f ", ft_slice_get(&s, i, j));
//         }
//         printf("\n");
//     }

//     int shape[2] = {4, 4};
//     ndarray *a = ft_create_ndarray(shape, 2, sizeof(int));
//     int *data = (int *)a->data;
//     for (int i = 0; i < 16; i++) data[i] = i + 1;
    
//     int start[2] = {1, 1};
//     int end[2] = {3, 3};
//     ndarray_view v = ft_slice_ndarray(a, start, end);
    
//     // Print sliced elements
//     for (int i = 0; i < v.shape[0]; i++) {
//         for (int j = 0; j < v.shape[1]; j++) {
//             int indices[2] = {i, j};
//             int *val = (int *)ft_get_view_element(&v, indices);
//             printf("%d ", *val);
//         }
//         printf("\n");
//     }

//     int shape4[2] = {4, 4};
// ndarray *arr4 = ft_create_ndarray(shape4, 2, sizeof(int));

// // Fill with values
// int *data4 = (int *)arr4->data;
// for (int i = 0; i < 16; i++)
//     data4[i] = i + 1;

// ft_print_ndarray(arr4, 'i');

// int start4[2] = {1, 1};
// int end4[2] = {3, 3};

// ndarray_view *view4 = ft_create_view(arr4, start4, end4);
// ft_print_view(view4, 'i');
// printf("%.4f", ft_ndarray_mean(arr4));

// ft_free_view(view4);
// // ft_free_ndarray(arr4);
    
//  // Example usage
//  int a_shape[] = {2, 3};
//  int b_shape[] = {3};
//  ndarray aa = {ft_malloc(6 * sizeof(int)), a_shape, 2, sizeof(int)};
//  ndarray bb = {ft_malloc(3 * sizeof(int)), b_shape, 1, sizeof(int)};

//  int *a_data = (int*) aa.data;
//  a_data[0] = 1; a_data[1] = 2; a_data[2] = 3;
//  a_data[3] = 4; a_data[4] = 5; a_data[5] = 6;

//  int *b_data = (int*) bb.data;
//  b_data[0] = 1; b_data[1] = 2; b_data[2] = 3;

//  ndarray *results = ft_ndarray_add(&aa, &bb);
//  ft_print_ndarray(results,'i');

//  // Free memory
//  ft_free(aa.data);
//  ft_free(bb.data);
//  ft_free(results->data);
//  ft_free(results->shape);
//  ft_free(results);




//another test

// int shape[2] = {5, 3};
// int strides[2] = {3 * sizeof(double), sizeof(double)};
// double data[] = {1.0, 2.0, 3.0, 4.0, NAN, 6.0, 7.0,7.0,7.0, 8.0, 8.0, 8.0, 8.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0
//     , 10.0, 10.0, 10.0, 10.0, 11.0, 11.0, 11.0, 11.0, 12.0, 12.0, 12.0, 12.0, 12.0
//     , 13.0, 13.0, 13.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 14.0, 15.0
//     , 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0
//     , 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0, 15.0};

// ndarray arr = {
//     .data = data,
//     .shape = shape,
//     .ndim = 2,
//     .itemsize = sizeof(double),
//     .strides = strides
// };

// printf("Head:\n");
// ft_ndarray_head(&arr, 3);

// printf("\nTail:\n");
// ft_ndarray_tail(&arr, 2);

// printf("\nDescribe:\n");
// ft_ndarray_describe(&arr);

// printf("\nSum:\n");
// ft_ndarray_sum_per_colunm(&arr);

// printf("\nIs NaN:\n");
// ft_ndarray_isnan(&arr);

// printf("\nFill NaN with 0:\n");
// ft_ndarray_fillna(&arr, 0.0);
// ft_ndarray_head(&arr, 5);

// printf("\nSum after fillna:\n");
// ft_ndarray_sum_per_colunm(&arr);

// printf("\nSort by column 1:\n");
// ft_ndarray_sort(&arr, 1);
// ft_ndarray_head(&arr, 5);

// printf("\nGroupby sum on column 0:\n");
// ft_ndarray_groupby_sum(&arr, 0);

// printf("\nApply square function:\n");
// ft_ndarray_apply(&arr, ft_square);
// ft_ndarray_head(&arr, 5);




   // Read CSV into ndarray
   ndarray arr = ft_ndarray_read_csv("data.csv");

   // Print ndarray info
   ft_ndarray_info(&arr);

   // Show the first 3 rows
   ft_ndarray_head(&arr, 3);

   // Describe ndarray (summary)
   ft_ndarray_describe(&arr);

   // Access column 1
   ndarray *col = ft_ndarray_column(&arr, 1);
   printf("Column 1:\n");
   ft_print_ndarray(col, 'i');
   ft_free_ndarray(col);

   // Drop the first row
   ft_ndarray_drop(&arr, 0, 0);  // Drop row
   printf("After dropping first row:\n");
   ft_print_ndarray(&arr, 'i');

   // Access row by label (label 2)
   ndarray *row = ft_ndarray_loc(&arr, 2);
   printf("Row 2:\n");
   ft_print_ndarray(row, 'i');
   ft_free_ndarray(row);

   // Access row by index (index 3)
   ndarray *row2 = ft_ndarray_iloc(&arr, 3);
   printf("Row 3 (iloc):\n");
   ft_print_ndarray(row2, 'i');
   ft_free_ndarray(row2);

   // Free ndarray memory
   ft_free_ndarray(&arr);
    return 0;
}
