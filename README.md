# Mini Pandas in C (ndarray-pandas)

A minimal pandas-like library built in pure C, integrated with a custom `ndarray` structure (NumPy style).

## Features

✅ `head()` - Show first N rows  
✅ `tail()` - Show last N rows  
✅ `describe()` - Summary statistics  
✅ `sum()` - Column-wise sum  
✅ `isnan()` - Detect NaN values  
✅ `fillna()` - Fill NaN with a value  
✅ `sort()` - Sort rows by column  
✅ `groupby_sum()` - Group by column and sum  
✅ `apply()` - Apply a function to all elements

---

## Installation

```bash
make
sudo make install
```

---

## Usage

```c
#include "ndarray_pandas.h"

int main() {
    int shape[2] = {5, 3};
    int strides[2] = {3 * sizeof(double), sizeof(double)};
    double data[15] = {1.0, 2.0, 3.0, 4.0, NAN, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0};

    ndarray arr = {
        .data = data,
        .shape = shape,
        .ndim = 2,
        .itemsize = sizeof(double),
        .strides = strides
    };

    ndarray_head(&arr, 3);
    ndarray_describe(&arr);
    ndarray_sum(&arr);
    ndarray_isnan(&arr);
    ndarray_fillna(&arr, 0.0);
    ndarray_sort(&arr, 1);
    ndarray_groupby_sum(&arr, 0);

    double square(double x) { return x * x; }
    ndarray_apply(&arr, square);

    return 0;
}
```

---

## Build & Run

```bash
make
./main
```

---

## Directory Structure

```
├── Makefile
├── README.md
├── main.c          // Usage Examples
├── ndarray.h       // ndarray Struct
├── ndarray.c       // ndarray Core
├── ndarray_pandas.h // Pandas-like API
├── ndarray_pandas.c // Implementation
```

---

## License
MIT

---

## Author
**Thiago** - Inspired by Python Pandas, built from scratch in C.
