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

vector_t* vector_new(size_t length);
vector_t* vector_new_view(linalg_t* parent, double* view, size_t length);
vector_t* vector_from_array(double* data, size_t length);
void vector_free(vector_t*);

vector_t* vector_constant(size_t length, double c);
vector_t* vector_zeros(size_t length);
vector_t* vector_ones(size_t length);
vector_t* vector_linspace(size_t length, double min, double max);

vector_t* vector_slice(vector_t* v, size_t start, size_t end);
vector_t* vector_copy(vector_t* v);
void vector_copy_into(vector_t* dst, vector_t* v);

vector_t* vector_add(vector_t* v1, vector_t* v2);
void vector_add_into(vector_t* dst, vector_t* v1, vector_t* v2);

vector_t* vector_sub(vector_t* v1, vector_t* v2);
void vector_sub_into(vector_t* dst, vector_t* v1, vector_t* v2);

vector_t* vector_scalar_mul(vector_t* v, double s);
void vector_scalar_mul_into(vector_t* dst, vector_t* v, double s);

vector_t* vector_normalize(vector_t* v);
void vector_normalize_into(vector_t* dst, vector_t* v);

double vector_dot(vector_t* v1, vector_t* v2);
double vector_norm(vector_t* v);

char* vector_to_string(vector_t* v);

bool vector_equal(vector_t* v1, vector_t* v2, double tol);

#endif