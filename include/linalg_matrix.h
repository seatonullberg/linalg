// linalg - C89 linear algebra library
// Copyright (C) Seaton Ullberg and contributors -- MIT license

#ifndef LINALG_MATRIX_H
#define LINALG_MATRIX_H

#ifndef _MATRIX_MACROS
#define _MATRIX_MACROS
#define MATRIX_ROW(m, i) ((i) / (m->nrows))
#define MATRIX_COL(m, i) ((i) % (m->nrows))
#define MATRIX_IDX(m, i, j) (((i) * (m->ncols)) + (j))
#define MATRIX_IDX_INTO(m, i, j) (DATA(m)[MATRIX_IDX(m, i, j)])
#endif

#include "linalg_base.h"
#include "linalg_vector.h"

typedef struct {
  linalg_t obj;
  size_t nrows;
  size_t ncols;
} matrix_t;

/** Returns a new matrix. */
matrix_t* matrix_new(size_t nrows, size_t ncols);
/** Returns a matrix initialized with the elements of a 1D array. */
matrix_t* matrix_from_array(double* data, size_t nrows, size_t ncols);
/** Returns a matrix initialized with the elements of a 2D array. */
matrix_t* matrix_from_2d_array(double** data, size_t nrows, size_t ncols);
/** Frees the memory of a matrix. */
void matrix_free(matrix_t* m);

/** Returns a matrix with all elements initialized to the same constant. */
matrix_t* matrix_constant(size_t nrows, size_t ncols, double c);
/** Returns a matrix with all elements initialized to 0. */
matrix_t* matrix_zeros(size_t nrows, size_t ncols);
/** Returns a matrix with all elements initialized to 1. */
matrix_t* matrix_ones(size_t nrows, size_t ncols);
/** Returns a square identity matrix. */
matrix_t* matrix_identity(size_t n);

/** Returns a copy of the matrix. */
matrix_t* matrix_copy(matrix_t* m);
/** Returns a vector view into a matrix row. */
vector_t* matrix_row_view(matrix_t*, size_t row);
/** Returns a vector copy of a matrix row. */
vector_t* matrix_row_copy(matrix_t*, size_t row);
/* No column view, columns are not contiguous memory. */
/** Returns a vector copy of a matrix column. */
vector_t* matrix_col_copy(matrix_t*, size_t col);

/** Copy a vector's data into a matrix row.
 *
 *  The matrix is modified in place.
 */
void matrix_copy_vector_into_row(matrix_t* m, vector_t* v, size_t row);
/** Copy a vector's data into a matrix column.
 *
 *  The matrix is modified in place.
 */
void matrix_copy_vector_into_col(matrix_t* m, vector_t* v, size_t col);

/** Returns a vector copy of the matrix diagonal. */
vector_t* matrix_diagonal(matrix_t* m);

/** Transposes the matrix in place. */
void matrix_transpose(matrix_t* m);

/** Compute the matrix product of two aligned matrices.
 *
 *  Iteration order is chosen to be i-k-j to optimize memory access.
 *  In this order, the innermost loop is accessing contiguous memory.
 */
matrix_t* matrix_mul(matrix_t* m1, matrix_t* m2);
/** Reads the result of the matrix product of two aligned matrices into `dst`.
 */
matrix_t* matrix_mul_into(matrix_t* dst, matrix_t* m1, matrix_t* m2);

/** Returns the product of an aligned matrix vector pair. */
vector_t* matrix_vector_mul(matrix_t* m, vector_t* v);

/** Returns true if the matrix is upper triangular to within a given tolerance.
 */
bool matrix_is_upper_triangular(matrix_t* m, double tol);

/** Returns true if matrices `m1` and `m2` are equal to within a given
 * tolerance. */
bool matrix_equal(matrix_t* m1, matrix_t* m2, double tol);

/** Returns the string representation of matrix `m`. */
char* matrix_to_string(matrix_t* m);

#endif