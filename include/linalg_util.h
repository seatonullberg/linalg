// linalg - C89 linear algebra library
// Copyright (C) Seaton Ullberg and contributors -- MIT license

#ifndef LINALG_UTIL_H
#define LINALG_UTIL_H

#include "linalg_error.h"

#ifndef CHECK_MEMORY
#define CHECK_MEMORY(memory) {                \
    if ((void*) memory == NULL) {             \
        raise_error(LINALG_ALLOCATION_ERROR); \
    }                                         \
}
#endif

#endif