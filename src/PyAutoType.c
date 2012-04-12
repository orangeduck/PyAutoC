#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "PyAutoError.h"
#include "PyAutoType.h"

#define MAX_TYPE_LEN 512
#define MAX_NUM_TYPES 1024

typedef char type_string[MAX_TYPE_LEN];
typedef int type_size;

type_string type_names[MAX_NUM_TYPES];
type_size type_sizes[MAX_NUM_TYPES];

int type_index = 0;

PyAutoType PyAutoType_Register(const char* type, int size) {
  
  for(int i = 0; i < type_index; i++) {
    if (strcmp(type, type_names[i]) == 0) return i;
  }
  
  if (strlen(type) >= MAX_TYPE_LEN) {
    PyAutoError("Type name '%s' longer than maximum %i characters.", type, MAX_TYPE_LEN);
  }
  
  if (type_index >= MAX_NUM_TYPES) {
    PyAutoError("Reached maximum of %i registered types!", MAX_NUM_TYPES);
  }
  
  strcpy(type_names[type_index], type);
  type_sizes[type_index] = size;
  type_index++;
  
  return type_index-1;
}

const char* PyAutoType_Name(PyAutoType id) {
  return type_names[id];
}

int PyAutoType_Size(PyAutoType id) {
  return type_sizes[id];
}