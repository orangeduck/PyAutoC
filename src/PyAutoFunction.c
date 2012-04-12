#include "PyAutoError.h"
#include "PyAutoType.h"
#include "PyAutoConvert.h"
#include "PyAutoFunction.h"

#define MAX_NAME_LEN 256
#define MAX_ARG_NUM 5
#define MAX_FUNC_ENTRIES 512

typedef struct {
  char name[MAX_NAME_LEN];
  PyAutoCFunc ac_func;
  void* func;
  PyAutoType type_id;
  int num_args;
  PyAutoType arg_types[MAX_ARG_NUM];
} func_entry;

static func_entry func_entries[MAX_FUNC_ENTRIES];
static int num_func_entries = 0;

static int total_arg_size(func_entry fe) {
  
  int total = 0;
  for(int i = 0; i < fe.num_args; i++) {
    total += PyAutoType_Size(fe.arg_types[i]);
  }
  return total;
  
}

static PyObject* PyAutoFunc_CallEntry(func_entry fe, PyObject* args) {

  void* ret_data = malloc(PyAutoType_Size(fe.type_id));
  void* arg_data = malloc(total_arg_size(fe));
  
  int arg_offset = 0;
  for(int j = 0; j < fe.num_args; j++) { 
    PyObject* py_arg = PyTuple_GetItem(args, j);
    PyAutoConvert_To_TypeId(fe.arg_types[j], py_arg, arg_data + arg_offset);
    arg_offset += PyAutoType_Size(fe.arg_types[j]);
  }
  
  fe.ac_func(ret_data, arg_data);
  
  PyObject* py_ret = PyAutoConvert_From_TypeId(fe.type_id, ret_data);
  
  free(arg_data);
  free(ret_data);
  return py_ret;

}

PyObject* PyAutoFunc_Call(void* c_func, PyObject* args) {
  
  for(int i = 0; i < num_func_entries; i++) {
    if (func_entries[i].func == c_func) return PyAutoFunc_CallEntry(func_entries[i], args);
  }
  
  PyAutoError("Function at %p is not registered!", c_func);
  
}

PyObject* PyAutoFunc_CallByName(char* c_func_name, PyObject* args) {

  for(int i = 0; i < num_func_entries; i++) {
    if (strcmp(func_entries[i].name, c_func_name) == 0) return PyAutoFunc_CallEntry(func_entries[i], args);
  }
  
  PyAutoError("Function %s is not registered!", c_func_name);


}

void PyAutoFunc_Register_TypeId(PyAutoCFunc ac_func, void* func, char* name, PyAutoType type_id, int num_args, ...) {
  
  if (num_args >= MAX_ARG_NUM) {
    PyAutoError("Function has %i arguments - maximum supported is %i", num_args, MAX_ARG_NUM);
  }
  
  if (strlen(name) >= MAX_NAME_LEN) {
    PyAutoError("Function name '%s' is longer than supported %i characters", name, MAX_NAME_LEN);
  }
  
  func_entry fe;
  strcpy(fe.name, name);
  fe.ac_func = ac_func;
  fe.func = func;
  fe.type_id = type_id;
  fe.num_args = num_args;
  
  va_list argl;
  va_start(argl, num_args);
  for(int i = 0; i < num_args; i++) {
    fe.arg_types[i] = va_arg(argl, PyAutoType);
  }
  
  func_entries[num_func_entries] = fe;
  num_func_entries++;
  
}