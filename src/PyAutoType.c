#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "PyAutoType.h"

typedef char* type_name;
typedef int type_size;

static type_name* type_names;
static type_size* type_sizes;

static int num_types = 0;
static int num_reserved_types = 128;

void PyAutoType_Initialize() {
  
  type_names = malloc(sizeof(type_name) * num_reserved_types);
  type_sizes = malloc(sizeof(type_size) * num_reserved_types);
  
}

void PyAutoType_Finalize() {
  
  for(int i = 0; i < num_types; i++) {
    free(type_names[i]);
  }
  
  free(type_names);
  free(type_sizes);
  
}

PyAutoType PyAutoType_Register(const char* type, int size) {
  
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

const char* PyAutoType_Name(PyAutoType id) {
  return type_names[id];
}

int PyAutoType_Size(PyAutoType id) {
  return type_sizes[id];
}