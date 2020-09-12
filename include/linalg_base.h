// linalg - C89 linear algebra library
// Copyright (C) Seaton Ullberg and contributors -- MIT license

#ifndef LINALG_BASE_H
#define LINALG_BASE_H

#include <stdbool.h>  // bool
#include <stddef.h>   // size_t
#include <stdlib.h>   // malloc

typedef struct linalg_t {
  bool owns_memory;
  struct linalg_t* memory_owner;
  int ref_count;
  double* data;
} linalg_t;

#ifndef OWNS_MEMORY
#define OWNS_MEMORY(obj) (((linalg_t*)obj)->owns_memory)
#endif

#ifndef MEMORY_OWNER
#define MEMORY_OWNER(obj) (((linalg_t*)obj)->memory_owner)
#endif

#ifndef REF_COUNT
#define REF_COUNT(obj) (((linalg_t*)obj)->ref_count)
#endif

#ifndef DATA
#define DATA(obj) (((linalg_t*)obj)->data)
#endif

#endif