#include "Python.h"
#include "PyAutoC.h"

static float add_numbers(int first, float second) {
  return first + second;
}

int main(int argc, char **argv) {
  
  Py_Initialize();
  PyAutoC_Initialize();
  
  PyAutoFunction_RegisterArgs2(add_numbers, float, int, float);

  PyObject* args = Py_BuildValue("(if)", 5, 6.13);
  PyObject* result = PyAutoFunction_Call(add_numbers, args);
  PyObject_Print(result, stdout, 0);
  
  Py_DECREF(result); Py_DECREF(args);
  
  PyAutoC_Finalize();
  Py_Finalize();
  
  return 0;
  
}
