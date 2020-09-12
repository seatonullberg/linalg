// linalg - C89 linear algebra library
// Copyright (C) Seaton Ullberg and contributors -- MIT license

#ifndef LINALG_VECTOR_H
#define LINALG_VECTOR_H

#ifndef _VECTOR_MACROS
#define _VECTOR_MACROS
#define VECTOR_IDX_INTO(v, i) (DATA(v)[i])
#endif

#include "linalg_base.h"

typedef struct {
  linalg_t obj;
  size_t length;
} vector_t;

/** Returns a new vector. */
vector_t* vector_new(size_t length);
/** Returns a vector which is a view into an existing vector.
 *
 *  The new vector and its parent share the same data. Mutating
 *  the data in either one will mutate both. This avoids a copy.
 */
vector_t* vector_new_view(linalg_t* parent, double* view, size_t length);
/** Returns a vector with elements from an existing array. */
vector_t* vector_from_array(double* data, size_t length);
/** Frees the memory of a vector. */
void vector_free(vector_t*);

/** Returns a vector with all elements initialized to the same constant. */
vector_t* vector_constant(size_t length, double c);
/** Returns a vector with all elements initialized to 0. */
vector_t* vector_zeros(size_t length);
/** Returns a vector with all elements initialized to 1. */
vector_t* vector_ones(size_t length);
/** Returns a new vector with each element equally spaced bewteen the closed
 * interval [min, max]. */
vector_t* vector_linspace(size_t length, double min, double max);

/** Returns a view into a segment of an existing vector.
 *
 *  The view is a reference to the segment of data in vector `v`
 *  from indices `start` to `end`.
 */
vector_t* vector_slice(vector_t* v, size_t start, size_t end);
/** Returns a copy of vector `v`. */
vector_t* vector_copy(vector_t* v);
/** Copies vector `v` into vector `dst`. */
void vector_copy_into(vector_t* dst, vector_t* v);

/** Returns the result of vector addition between `v1` and `v2`. */
vector_t* vector_add(vector_t* v1, vector_t* v2);
/** Reads the result of vector addition between `v1` and `v2` into `dst`. */
void vector_add_into(vector_t* dst, vector_t* v1, vector_t* v2);

/** Returns the result of vector subtraction between `v1` and `v2`. */
vector_t* vector_sub(vector_t* v1, vector_t* v2);
/** Reads the result of vector subtraction between `v1` and `v2` into `dst`. */
void vector_sub_into(vector_t* dst, vector_t* v1, vector_t* v2);

/** Returns the result of vector * scalar multiplication between `v` and `s`. */
vector_t* vector_scalar_mul(vector_t* v, double s);
/** Reads the result of vector * scalar multiplication between `v` and `s` into
 * `dst`. */
void vector_scalar_mul_into(vector_t* dst, vector_t* v, double s);

/** Returns the normalization of vector `v`. */
vector_t* vector_normalize(vector_t* v);
/** Reads the result of the normalization of vector `v` into `dst`. */
void vector_normalize_into(vector_t* dst, vector_t* v);

/** Returns the dot product of vectors `v1` and `v2`. */
double vector_dot(vector_t* v1, vector_t* v2);
/** Returns the L2 norm of vector `v`. */
double vector_norm(vector_t* v);

/** Returns the string representation of vector `v`. */
char* vector_to_string(vector_t* v);

/** Returns true if vectors v1 and v2 are equivalent within a given tolerance.
 */
bool vector_equal(vector_t* v1, vector_t* v2, double tol);

#endif