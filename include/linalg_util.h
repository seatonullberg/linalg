// linalg - C89 linear algebra library
// Copyright (C) Seaton Ullberg and contributors -- MIT license

#ifndef LINALG_UTIL_H
#define LINALG_UTIL_H

#include "linalg_error.h"

#ifndef CHECK_MEMORY
/** Raises LINALG_ALLOCATION_ERROR if `memory` is NULL. */
#define CHECK_MEMORY(memory)                \
  {                                         \
    if ((void*)memory == NULL) {            \
      raise_error(LINALG_ALLOCATION_ERROR); \
    }                                       \
  }
#endif

#ifndef CHECK_REF_COUNT
/** Raises LINALG_NONZERO_REFERENCE_ERROR if `obj` has more than 0 references to it. */
#define CHECK_REF_COUNT(obj)                       \
  {                                                \
    if (REF_COUNT(obj) != 0) {                     \
      raise_error(LINALG_NONZERO_REFERENCE_ERROR); \
    }                                              \
  }
#endif

#endif