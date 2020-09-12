// linalg - C89 linear algebra library
// Copyright (C) Seaton Ullberg and contributors -- MIT license

#include <math.h>

#include "linalg_util.h"
#include "linalg_vector.h"

vector_t* vector_new(size_t length) {
    vector_t* v = malloc(sizeof(vector_t));
    CHECK_MEMORY(v);
    DATA(v) = malloc((sizeof(double)) * length);
    CHECK_MEMORY(v);
    v->length = length;
    OWNS_MEMORY(v) = true;
    MEMORY_OWNER(v) = NULL;
    REF_COUNT(v) = 0;
    return v;
}

vector_t* vector_from_array(double* data, size_t length) {
    vector_t* v = vector_new(length);
    size_t i;
    for (i = 0; i < v->length; i++) {
        VECTOR_IDX_INTO(v, i) = data[i];
    }
    return v;
}

vector_t* vector_constant(size_t length, double c) {
    vector_t* v = vector_new(length);
    size_t i;
    for (i = 0; i < v->length; i++) {
        VECTOR_IDX_INTO(v, i) = c;
    }
    return v;
}

vector_t* vector_zeros(size_t length) {
    return vector_constant(length, 0);
}

vector_t* vector_ones(size_t length) {
    return vector_constant(length, 1);
}

bool vector_equal(vector_t* v1, vector_t* v2, double tol) {
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