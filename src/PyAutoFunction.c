#include "PyAutoC.h"

#define MAX_ARG_NUM 10

typedef struct {
  char* name;
  void* src_func;
  PyAutoCFunc ac_func;
  PyAutoType type_id;
  int num_args;
  PyAutoType arg_types[MAX_ARG_NUM];
} func_entry;

static PyAutoHashtable* func_name_table;
static PyAutoHashtable* func_ptr_table;

void PyAutoFunction_Initialize(void) {
  func_name_table = PyAutoHashtable_New(1024);
  func_ptr_table = PyAutoHashtable_New(1024);
}

static void func_entry_delete(func_entry* fe) {
  free(fe->name);
  free(fe);
}

void PyAutoFunction_Finalize(void) {
  PyAutoHashtable_Map(func_name_table, (void(*)(void*))func_entry_delete);
  PyAutoHashtable_Delete(func_name_table);
  PyAutoHashtable_Delete(func_ptr_table);
}

static int total_arg_size(func_entry* fe) {
  
  int total = 0;
  for(int i = 0; i < fe->num_args; i++) {
    total += PyAutoType_Size(fe->arg_types[i]);
  }
  return total;
  
}

#define ret_stack_size 128
#define arg_stack_size 1024

static char ret_stack[ret_stack_size];
static void* ret_stack_ptr = ret_stack;

static char arg_stack[arg_stack_size];
static void* arg_stack_ptr = arg_stack;

static int ret_stack_space() {
  return (void*)ret_stack - ret_stack_ptr + ret_stack_size;
}

static int arg_stack_space() {
  return (void*)arg_stack - arg_stack_ptr + arg_stack_size;
}

static PyObject* PyAutoFunction_CallEntry(func_entry* fe, PyObject* args) {
  
  int ret_data_size = PyAutoType_Size(fe->type_id);
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
  
  for(int j = 0; j < fe->num_args; j++) { 
    PyObject* py_arg = PyTuple_GetItem(args, j);
    
    if (py_arg == NULL) {
      if (ret_using_heap) free(ret_data);
      if (arg_using_heap) free(arg_data);
      return PyErr_Format(PyExc_TypeError, "PyAutoFunction: Function '%s' called with too few arguments. Expected %i, recieved %i.", fe->name, fe->num_args, j);
    }
    
    PyAutoConvert_To_TypeId(fe->arg_types[j], py_arg, arg_data);
    
    if (PyErr_Occurred()) {
      if (ret_using_heap) free(ret_data);
      if (arg_using_heap) free(arg_data);
      return NULL;
    }
    
    arg_data += PyAutoType_Size(fe->arg_types[j]);
  }
  
  ret_data += ret_data_size;
  
  /* If not using heap update stack pointers */
  if (!ret_using_heap) { ret_stack_ptr = ret_data; }
  if (!arg_using_heap) { arg_stack_ptr = arg_data; }
  
  arg_data -= arg_data_size;
  ret_data -= ret_data_size;
  
  fe->ac_func(ret_data, arg_data);
  PyObject* py_ret = PyAutoConvert_From_TypeId(fe->type_id, ret_data);
  
  /* Either free heap data or reduce stack pointers */
  if (ret_using_heap) { free(ret_data); } else { ret_stack_ptr -= ret_data_size; } 
  if (arg_using_heap) { free(arg_data); } else { arg_stack_ptr -= arg_data_size; }
  
  return py_ret;
  
}

PyObject* PyAutoFunction_Call(void* func, PyObject* args) {

  char ptr_string[128];
  sprintf(ptr_string, "%p", func);

  func_entry* fe = PyAutoHashtable_Get(func_ptr_table, ptr_string);
  if (fe != NULL) {
    return PyAutoFunction_CallEntry(fe, args);
  }
  
  return PyErr_Format(PyExc_NameError, "PyAutoFunction: Function address '%p' is not registered!", func);
}

PyObject* PyAutoFunction_CallByName(char* c_func_name, PyObject* args) {

  func_entry* fe = PyAutoHashtable_Get(func_name_table, c_func_name);
  if (fe != NULL) {
    return PyAutoFunction_CallEntry(fe, args);
  }
  
  return PyErr_Format(PyExc_NameError, "PyAutoFunction: Function '%s' is not registered!", c_func_name);
}

void PyAutoFunction_Register_TypeId(void* src_func, PyAutoCFunc ac_func, char* name, PyAutoType type_id, int num_args, ...) {
  
  if (num_args >= MAX_ARG_NUM) {
    PyErr_Format(PyExc_Exception, "PyAutoFunction: Function has %i arguments - maximum supported is %i", num_args, MAX_ARG_NUM);
    return;
  }
  
  func_entry* fe = malloc(sizeof(func_entry));
  fe->name = malloc(strlen(name) + 1);
  strcpy(fe->name, name);
  fe->src_func = src_func;
  fe->ac_func = ac_func;
  fe->type_id = type_id;
  fe->num_args = num_args;
  
  va_list argl;
  va_start(argl, num_args);
  for(int i = 0; i < num_args; i++) {
    fe->arg_types[i] = va_arg(argl, PyAutoType);
  }
  
  char ptr_string[128];
  sprintf(ptr_string, "%p", src_func);
  
  PyAutoHashtable_Set(func_name_table, name, fe);
  PyAutoHashtable_Set(func_ptr_table, ptr_string, fe);
  
}
