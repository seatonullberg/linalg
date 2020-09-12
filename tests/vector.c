// linalg - C89 linear algebra library
// Copyright (C) Seaton Ullberg and contributors -- MIT license

#include <math.h>
#include <string.h>

#include "linalg_vector.h"
#include "utest.h"

UTEST(vector_tests, test_vector_constant) {
  vector_t* v = vector_constant(3, 2.5);
  double arr[] = {2.5, 2.5, 2.5};
  vector_t* target = vector_from_array(arr, 3);
  ASSERT_TRUE(vector_equal(v, target, 1.0e-6));
  vector_free(v);
  vector_free(target);
}

UTEST(vector_tests, test_vector_zeros) {
  vector_t* v = vector_zeros(3);
  double arr[] = {0.0, 0.0, 0.0};
  vector_t* target = vector_from_array(arr, 3);
  ASSERT_TRUE(vector_equal(v, target, 1.0e-6));
  vector_free(v);
  vector_free(target);
}

UTEST(vector_tests, test_vector_ones) {
  vector_t* v = vector_ones(3);
  double arr[] = {1.0, 1.0, 1.0};
  vector_t* target = vector_from_array(arr, 3);
  ASSERT_TRUE(vector_equal(v, target, 1.0e-6));
  vector_free(v);
  vector_free(target);
}

UTEST(vector_tests, test_vector_linspace) {
  vector_t* v = vector_linspace(3, 1.0, 3.0);
  double arr[] = {1.0, 2.0, 3.0};
  vector_t* target = vector_from_array(arr, 3);
  ASSERT_TRUE(vector_equal(v, target, 1.0e-6));
  vector_free(v);
  vector_free(target);
}

UTEST(vector_tests, test_vector_add) {
  double arr1[] = {0.0, 1.0, 1.0};
  vector_t* v1 = vector_from_array(arr1, 3);
  double arr2[] = {1.0, 1.0, 1.0};
  vector_t* v2 = vector_from_array(arr2, 3);
  double arr_target[] = {1.0, 2.0, 2.0};
  vector_t* target = vector_from_array(arr_target, 3);
  vector_t* v = vector_add(v1, v2);
  ASSERT_TRUE(vector_equal(v, target, 1.0e-6));
  vector_free(v1);
  vector_free(v2);
  vector_free(v);
  vector_free(target);
}

UTEST(vector_tests, test_vector_sub) {
  double arr1[] = {0.0, 1.0, 1.0};
  vector_t* v1 = vector_from_array(arr1, 3);
  double arr2[] = {1.0, 1.0, 1.0};
  vector_t* v2 = vector_from_array(arr2, 3);
  double arr_target[] = {-1.0, 0.0, 0.0};
  vector_t* target = vector_from_array(arr_target, 3);
  vector_t* v = vector_sub(v1, v2);
  ASSERT_TRUE(vector_equal(v, target, 1.0e-6));
  vector_free(v1);
  vector_free(v2);
  vector_free(v);
  vector_free(target);
}

UTEST(vector_tests, test_vector_scalar_mul) {
  double arr[] = {0.0, 1.0, 1.0};
  vector_t* v = vector_from_array(arr, 3);
  double s = 2.0;
  double arr_target[] = {0.0, 2.0, 2.0};
  vector_t* target = vector_from_array(arr_target, 3);
  vector_t* res = vector_scalar_mul(v, s);
  ASSERT_TRUE(vector_equal(res, target, 1.0e-6));
  vector_free(v);
  vector_free(target);
  vector_free(res);
}

UTEST(vector_tests, test_vector_normalize) {
  double arr[] = {1.0, 1.0, 0.0};
  vector_t* v = vector_from_array(arr, 3);
  double arr_target[] = {1.0 / sqrt(2.0), 1.0 / sqrt(2.0), 0.0};
  vector_t* target = vector_from_array(arr_target, 3);
  vector_t* res = vector_normalize(v);
  ASSERT_TRUE(vector_equal(res, target, 1.0e-6));
  vector_free(v);
  vector_free(target);
  vector_free(res);
}

UTEST(vector_tests, test_vector_dot) {
  double arr1[] = {1.0, 1.0, 0.0};
  vector_t* v1 = vector_from_array(arr1, 3);
  double arr2[] = {0.0, 1.0, 1.0};
  vector_t* v2 = vector_from_array(arr2, 3);
  double res = vector_dot(v1, v2);
  double target = 1.0;
  ASSERT_EQ(res, target);
  vector_free(v1);
  vector_free(v2);
}

UTEST(vector_tests, test_vector_norm) {
  double arr[] = {1.0, 1.0, 1.0};
  vector_t* v = vector_from_array(arr, 3);
  double res = vector_norm(v);
  double target = sqrt(3);
  ASSERT_EQ(res, target);
  vector_free(v);
}

UTEST(vector_tests, test_vector_to_string) {
  double arr[] = {1.0, 2.0, 3.0};
  vector_t* v = vector_from_array(arr, 3);
  char* res = vector_to_string(v);
  char* target = "[1.000000, 2.000000, 3.000000]";
  ASSERT_EQ(strcmp(res, target), 0);
  vector_free(v);
  free(res);
}