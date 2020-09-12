// linalg - C89 linear algebra library
// Copyright (C) Seaton Ullberg and contributors -- MIT license

#include "linalg_vector.h"
#include "utest.h"

UTEST(vector_tests, test_vector_zeros) {
    vector_t* v = vector_zeros(3);
    double arr[] = {0.0, 0.0, 0.0};
    vector_t* target = vector_from_array(arr, 3);
    ASSERT_TRUE(vector_equal(v, target, 1.0e-6));
}

UTEST(vector_tests, test_vector_ones) {
    vector_t* v = vector_ones(3);
    double arr[] = {1.0, 1.0, 1.0};
    vector_t* target = vector_from_array(arr, 3);
    ASSERT_TRUE(vector_equal(v, target, 1.0e-6));
}