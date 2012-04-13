#include "PyAutoType.h"
#include "PyAutoConvert.h"
#include "PyAutoFunction.h"

#define MAX_ARG_NUM 5

typedef struct {
  char* name;
  PyAutoCFunc ac_func;
  void* func;
  PyAutoType type_id;
  int num_args;
  PyAutoType arg_types[MAX_ARG_NUM];
} func_entry;

static func_entry* func_entries;
static int num_func_entries = 0;
static int num_reserved_func_entries = 512;

void PyAutoFunction_Initialize() {
  func_entries = malloc(sizeof(func_entry) * num_reserved_func_entries);
}

void PyAutoFunction_Finalize() {

  for(int i = 0; i < num_func_entries; i++) {
    free(func_entries[i].name);
  }

  free(func_entries);
}

static int total_arg_size(func_entry fe) {
  
  int total = 0;
  for(int i = 0; i < fe.num_args; i++) {
    total += PyAutoType_Size(fe.arg_types[i]);
  }
  return total;
  
}

static PyObject* PyAutoFunction_CallEntry(func_entry fe, PyObject* args) {

  void* ret_data = malloc(PyAutoType_Size(fe.type_id));
  void* arg_data = malloc(total_arg_size(fe));
  
  int arg_offset = 0;
  for(int j = 0; j < fe.num_args; j++) { 
    PyObject* py_arg = PyTuple_GetItem(args, j);
    PyObject* err = PyAutoConvert_To_TypeId(fe.arg_types[j], py_arg, arg_data + arg_offset);
    if (err == NULL) { return NULL; } else { Py_DECREF(err); }
    arg_offset += PyAutoType_Size(fe.arg_types[j]);
  }
  
  fe.ac_func(ret_data, arg_data);
  
  PyObject* py_ret = PyAutoConvert_From_TypeId(fe.type_id, ret_data);
  
  free(arg_data);
  free(ret_data);
  
  return py_ret;
  
}

PyObject* PyAutoFunction_Call(void* c_func, PyObject* args) {
  
  for(int i = 0; i < num_func_entries; i++) {
    if (func_entries[i].func == c_func) return PyAutoFunction_CallEntry(func_entries[i], args);
  }
  
  PyErr_Format(PyExc_NameError, "Function at %p is not registered!", c_func);
  return NULL;
  
}

PyObject* PyAutoFunction_CallByName(char* c_func_name, PyObject* args) {

  for(int i = 0; i < num_func_entries; i++) {
    if (strcmp(func_entries[i].name, c_func_name) == 0) return PyAutoFunction_CallEntry(func_entries[i], args);
  }
  
  PyErr_Format(PyExc_NameError, "Function %s is not registered!", c_func_name);
  return NULL;

}

void PyAutoFunction_Register_TypeId(PyAutoCFunc ac_func, void* func, char* name, PyAutoType type_id, int num_args, ...) {
  
  if (num_args >= MAX_ARG_NUM) {
    PyErr_Format(PyExc_Exception, "Function has %i arguments - maximum supported is %i", num_args, MAX_ARG_NUM);
    return;
  }
  
  if (num_func_entries >= num_reserved_func_entries) {
    num_reserved_func_entries += 512;
    func_entries = realloc(func_entries, sizeof(func_entry) * num_reserved_func_entries);
  }
  
  func_entry fe;
  fe.name = malloc(strlen(name) + 1);
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