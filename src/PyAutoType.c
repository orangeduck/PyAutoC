#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "PyAutoC.h"

typedef char* type_name;
typedef size_t type_size;

static type_name* type_names;
static type_size* type_sizes;

static int num_types = 0;
static int num_reserved_types = 128;

void PyAutoType_Initialize(void) {
  
  type_names = malloc(sizeof(type_name) * num_reserved_types);
  type_sizes = malloc(sizeof(type_size) * num_reserved_types);
}

void PyAutoType_Finalize(void) {
  
  for(int i = 0; i < num_types; i++) {
    free(type_names[i]);
  }
  
  free(type_names);
  free(type_sizes);
}

PyAutoType PyAutoType_Register(const char* type, size_t size) {
  
  for(int i = 0; i < num_types; i++) {
    if (strcmp(type, type_names[i]) == 0) return i;
  }
  
  if (num_types >= num_reserved_types) {
    num_reserved_types += 128;
    type_names = realloc(type_names, sizeof(type_name) * num_reserved_types);
    type_sizes = realloc(type_sizes, sizeof(type_size) * num_reserved_types);
  }
  
  type_names[num_types] = malloc(strlen(type)+1);
  strcpy(type_names[num_types], type);
  type_sizes[num_types] = size;
  num_types++;
  
  return num_types-1;
}

PyAutoType PyAutoType_Find(const char* type) {

  for(int i = 0; i < num_types; i++) {
    if (strcmp(type, type_names[i]) == 0) return i;
  }
  
  return PYAUTOC_INVALID_TYPE;
}

const char* PyAutoType_Name(PyAutoType id) {
  if (id == PYAUTOC_INVALID_TYPE) return "Unknown Type";
  return type_names[id];
}

size_t PyAutoType_Size(PyAutoType id) {
  if (id == PYAUTOC_INVALID_TYPE) return -1;
  return type_sizes[id];
}
