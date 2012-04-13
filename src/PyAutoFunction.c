#include "PyAutoType.h"
#include "PyAutoConvert.h"
#include "PyAutoFunction.h"

#define MAX_ARG_NUM 10

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
static int num_reserved_func_entries = 128;

void PyAutoFunction_Initialize(void) {
  func_entries = malloc(sizeof(func_entry) * num_reserved_func_entries);
}

void PyAutoFunction_Finalize(void) {

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

#define ret_stack_size 128
#define arg_stack_size 1024

static char ret_stack[128];
static void* ret_stack_ptr = ret_stack;

static char arg_stack[1024];
static void* arg_stack_ptr = arg_stack;

static int ret_stack_space() {
  return (void*)ret_stack - ret_stack_ptr + ret_stack_size;
}

static int arg_stack_space() {
  return (void*)arg_stack - arg_stack_ptr + arg_stack_size;
}

static PyObject* PyAutoFunction_CallEntry(func_entry fe, PyObject* args) {
  
  int ret_data_size = PyAutoType_Size(fe.type_id);
  int arg_data_size = total_arg_size(fe);
  
  int ret_using_heap = 0; int arg_using_heap = 0;
  void* ret_data = ret_stack_ptr;
  void* arg_data = arg_stack_ptr;
  
  if (ret_data_size > ret_stack_space()) {
    ret_using_heap = 1; ret_data = malloc(ret_data_size);
  }
  
  if (arg_data_size > arg_stack_space()) {
    arg_using_heap = 1; arg_data = malloc(arg_data_size);
  }
  
  for(int j = 0; j < fe.num_args; j++) { 
    PyObject* py_arg = PyTuple_GetItem(args, j);
    PyAutoConvert_To_TypeId(fe.arg_types[j], py_arg, arg_data);
    
    if (PyErr_Occurred()) {
      if (ret_using_heap) free(ret_data);
      if (arg_using_heap) free(arg_data);
      return NULL;
    }
    
    arg_data += PyAutoType_Size(fe.arg_types[j]);
  }
  
  /* If not using heap update stack pointers */
  if (!ret_using_heap) ret_stack_ptr = ret_data;
  if (!arg_using_heap) arg_stack_ptr = arg_data;
  
  fe.ac_func(ret_data, arg_data);
  PyObject* py_ret = PyAutoConvert_From_TypeId(fe.type_id, ret_data);
  
  /* Either free heap data or reduce stack pointers */
  if (ret_using_heap) { free(ret_data); } else { ret_stack_ptr -= ret_data_size; } 
  if (arg_using_heap) { free(arg_data); } else { arg_stack_ptr -= arg_data_size; }
  
  return py_ret;
  
}

PyObject* PyAutoFunction_Call(void* c_func, PyObject* args) {
  
  for(int i = 0; i < num_func_entries; i++) {
    if (func_entries[i].func == c_func) return PyAutoFunction_CallEntry(func_entries[i], args);
  }
  
  return PyErr_Format(PyExc_NameError, "Function at %p is not registered!", c_func);
  
}

PyObject* PyAutoFunction_CallByName(char* c_func_name, PyObject* args) {

  for(int i = 0; i < num_func_entries; i++) {
    if (strcmp(func_entries[i].name, c_func_name) == 0) return PyAutoFunction_CallEntry(func_entries[i], args);
  }
  
  return PyErr_Format(PyExc_NameError, "Function %s is not registered!", c_func_name);

}

void PyAutoFunction_Register_TypeId(PyAutoCFunc ac_func, void* func, char* name, PyAutoType type_id, int num_args, ...) {
  
  if (num_args >= MAX_ARG_NUM) {
    PyErr_Format(PyExc_Exception, "Function has %i arguments - maximum supported is %i", num_args, MAX_ARG_NUM);
    return;
  }
  
  if (num_func_entries >= num_reserved_func_entries) {
    num_reserved_func_entries += 128;
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
