#include "Python.h"
#include "PyAutoC.h"

static float add_numbers(int first, float second) {
  printf("%i\n", first);
  printf("%f\n", second);
  return first + second;
}

static void hello_world(char* message) {
  printf("Hello %s!\n", message);
}

typedef struct {
  float x, y, z;
} vector3;

static void PyObject_PrintStdout(PyObject* p) {
  
  PyObject* pstr = PyObject_Str(p);
  char* cstr = PyString_AsString(pstr);
  printf("%s\n", cstr);
  Py_DECREF(pstr);
  
}

int main() {
  
  Py_Initialize();
  
  PyAutoConvert_RegisterPrimatives();
  PyAutoFunction_RegisterArgs2(add_numbers, float, int, float);
  PyAutoFunction_RegisterVoidArgs1(hello_world, void, char*);
  
  PyObject* args0 = Py_BuildValue("(if)", 5, 6.13);
  PyObject* result0 = PyAutoFunction_Call(add_numbers, args0);
  PyObject_PrintStdout(result0);
  Py_DECREF(result0); Py_DECREF(args0);
  
  PyObject* args1 = Py_BuildValue("(s)", "Daniel");
  PyObject* result1 = PyAutoFunction_Call(hello_world, args1);
  PyObject_PrintStdout(result1);
  Py_DECREF(result1); Py_DECREF(args1);
  
  PyAutoStruct_Register(vector3);
  PyAutoStruct_RegisterMember(vector3, x, float);
  PyAutoStruct_RegisterMember(vector3, y, float);
  PyAutoStruct_RegisterMember(vector3, z, float);
  
  vector3 position = {1.0f, 2.11f, 3.16f};
  
  PyObject* result2 = PyAutoStruct_Get(vector3, &position, y);
  PyObject_PrintStdout(result2);
  Py_DECREF(result2);
  
  Py_Finalize();
  
  return 0;
  
}