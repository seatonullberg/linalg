// linalg - C89 linear algebra library
// Copyright (C) Seaton Ullberg and contributors -- MIT license

#ifndef LINALG_ERROR_H
#define LINALG_ERROR_H

#include <stdio.h>
#include <stdlib.h>

/** Custom error codes. */
typedef enum {
  /** Successful termination. */
  LINALG_SUCCESS,
  /** Unknown fatal error. */
  LINALG_UNKNOWN_ERROR,
  /** Memory allocation error. */
  LINALG_ALLOCATION_ERROR,
  /** Reference count error. */
  LINALG_NONZERO_REFERENCE_ERROR,
} linalg_error_t;

/** Prints an error code's message then exits. */
void raise_error(linalg_error_t error) {
  switch (error) {
  LINALG_SUCCESS:
    exit(EXIT_SUCCESS);
  LINALG_UNKNOWN_ERROR:
    printf("encountered unknown error");
  LINALG_ALLOCATION_ERROR:
    printf("memory allocation error");
  LINALG_NONZERO_REFERENCE_ERROR:
    printf("cannot free memory with non-zero reference count");
  }
  exit(EXIT_FAILURE);
}

#endif