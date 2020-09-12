// linalg - C89 linear algebra library
// Copyright (C) Seaton Ullberg and contributors -- MIT license

#include <math.h>
#include <string.h>

#include "linalg_util.h"
#include "linalg_vector.h"

/** Returns a new vector. */
vector_t *vector_new(size_t length) {
  vector_t *v = malloc(sizeof(vector_t));
  CHECK_MEMORY(v);
  DATA(v) = malloc((sizeof(double)) * length);
  CHECK_MEMORY(v);
  v->length = length;
  OWNS_MEMORY(v) = true;
  MEMORY_OWNER(v) = NULL;
  REF_COUNT(v) = 0;
  return v;
}

/** Returns a vector which is a view into an existing vector.
 *
 *  The new vector and its parent share the same data. Mutating
 *  the data in either one will mutate both. This avoids a copy.
 */
vector_t *vector_new_view(linalg_t *parent, double *view, size_t length) {
  vector_t *v = malloc(sizeof(vector_t));
  CHECK_MEMORY(v);
  DATA(v) = view;
  v->length = length;
  OWNS_MEMORY(v) = false;
  MEMORY_OWNER(v) = parent;
  REF_COUNT(v) = 0;
  REF_COUNT(parent) += 1;
  return v;
}

/** Returns a vector with elements from an existing array. */
vector_t *vector_from_array(double *data, size_t length) {
  vector_t *v = vector_new(length);
  size_t i;
  for (i = 0; i < v->length; i++) {
    VECTOR_IDX_INTO(v, i) = data[i];
  }
  return v;
}

/** Frees the memory of a vector. */
void vector_free(vector_t *v) {
  linalg_t *memory_owner;
  CHECK_REF_COUNT(v);
  if (OWNS_MEMORY(v)) {
    free(DATA(v));
    free(v);
  } else {
    memory_owner = MEMORY_OWNER(v);
    REF_COUNT(memory_owner) -= 1;
    free(v);
  }
}

/** Returns a vector with all elements initialized to the same constant. */
vector_t *vector_constant(size_t length, double c) {
  vector_t *v = vector_new(length);
  size_t i;
  for (i = 0; i < v->length; i++) {
    VECTOR_IDX_INTO(v, i) = c;
  }
  return v;
}

/** Returns a vector with all elements initialized to 0. */
vector_t *vector_zeros(size_t length) { return vector_constant(length, 0); }

/** Returns a vector with all elements initialized to 1. */
vector_t *vector_ones(size_t length) { return vector_constant(length, 1); }

/** Returns a new vector with each element equally spaced bewteen the closed
 * interval [min, max]. */
vector_t *vector_linspace(size_t length, double min, double max) {
  vector_t *v = vector_new(length);
  double step = (max - min) / (length - 1);
  size_t i;
  for (i = 0; i < v->length; i++) {
    VECTOR_IDX_INTO(v, i) = min + step * i;
  }
  return v;
}

/** Returns a view into a segment of an existing vector.
 *
 *  The view is a reference to the segment of data in vector `v`
 *  from indices `start` to `end`.
 */
vector_t *vector_slice(vector_t *v, size_t start, size_t end) {
  size_t length = end - start;
  double *start_ptr = DATA(v) + start;
  vector_t *view = vector_new_view((linalg_t *)v, start_ptr, length);
  return view;
}

/** Returns a copy of vector `v`. */
vector_t *vector_copy(vector_t *v) {
  vector_t *copy = vector_new(v->length);
  vector_copy_into(copy, v);
  return copy;
}

/** Copies vector `v` into vector `dst`. */
void vector_copy_into(vector_t *dst, vector_t *v) {
  size_t i;
  for (i = 0; i < v->length; i++) {
    VECTOR_IDX_INTO(dst, i) = VECTOR_IDX_INTO(v, i);
  }
}

/** Returns the result of vector addition between `v1` and `v2`. */
vector_t *vector_add(vector_t *v1, vector_t *v2) {
  vector_t *v = vector_new(v1->length);
  vector_add_into(v, v1, v2);
  return v;
}

/** Reads the result of vector addition between `v1` and `v2` into `dst`. */
void vector_add_into(vector_t *dst, vector_t *v1, vector_t *v2) {
  size_t i;
  for (i = 0; i < v1->length; i++) {
    VECTOR_IDX_INTO(dst, i) = VECTOR_IDX_INTO(v1, i) + VECTOR_IDX_INTO(v2, i);
  }
}

/** Returns the result of vector subtraction between `v1` and `v2`. */
vector_t *vector_sub(vector_t *v1, vector_t *v2) {
  vector_t *v = vector_new(v1->length);
  vector_sub_into(v, v1, v2);
  return v;
}

/** Reads the result of vector subtraction between `v1` and `v2` into `dst`. */
void vector_sub_into(vector_t *dst, vector_t *v1, vector_t *v2) {
  size_t i;
  for (i = 0; i < v1->length; i++) {
    VECTOR_IDX_INTO(dst, i) = VECTOR_IDX_INTO(v1, i) - VECTOR_IDX_INTO(v2, i);
  }
}

/** Returns the result of vector * scalar multiplication between `v` and `s`. */
vector_t *vector_scalar_mul(vector_t *v, double s) {
  vector_t *res = vector_new(v->length);
  vector_scalar_mul_into(res, v, s);
  return res;
}

/** Reads the result of vector * scalar multiplication between `v` and `s` into
 * `dst`. */
void vector_scalar_mul_into(vector_t *dst, vector_t *v, double s) {
  size_t i;
  for (i = 0; i < v->length; i++) {
    VECTOR_IDX_INTO(dst, i) = VECTOR_IDX_INTO(v, i) * s;
  }
}

/** Returns the normalization of vector `v`. */
vector_t *vector_normalize(vector_t *v) {
  vector_t *res = vector_new(v->length);
  double norm = vector_norm(v);
  vector_normalize_into(res, v);
  return res;
}

/** Reads the result of the normalization of vector `v` into `dst`. */
void vector_normalize_into(vector_t *dst, vector_t *v) {
  double norm = vector_norm(v);
  size_t i;
  for (i = 0; i < v->length; i++) {
    VECTOR_IDX_INTO(dst, i) = VECTOR_IDX_INTO(v, i) / norm;
  }
}

/** Returns the dot product of vectors `v1` and `v2`. */
double vector_dot(vector_t *v1, vector_t *v2) {
  double prod = 0;
  size_t i;
  for (i = 0; i < v1->length; i++) {
    prod += VECTOR_IDX_INTO(v1, i) * VECTOR_IDX_INTO(v2, i);
  }
  return prod;
}

/** Returns the L2 norm of vector `v`. */
double vector_norm(vector_t *v) { return sqrt(vector_dot(v, v)); }

/** Returns true if vectors v1 and v2 are equivalent within a given tolerance.
 */
bool vector_equal(vector_t *v1, vector_t *v2, double tol) {
  if (v1->length != v2->length) {
    return false;
  }
  size_t i;
  for (i = 0; i < v1->length; i++) {
    if (fabs(VECTOR_IDX_INTO(v1, i) - VECTOR_IDX_INTO(v2, i)) > tol) {
      return false;
    }
  }
  return true;
}

/** Returns the string representation of vector `v`. */
char *vector_to_string(vector_t *v) {
  char *s;
  char *str = malloc(sizeof(char) * 256);  // totally arbitrary buffer size
  strcat(str, "[");
  size_t i;
  for (i = 0; i < v->length; i++) {
    sprintf(s, "%f", VECTOR_IDX_INTO(v, i));
    if (i != v->length - 1) {
      strcat(s, ", ");
    }
    strcat(str, s);
  }
  strcat(str, "]");
  return str;
}