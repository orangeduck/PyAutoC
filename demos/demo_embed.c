#include "Python.h"
#include "PyAutoC.h"

typedef struct {
  char* name;
  float value;
} my_class;

static my_class test_my_class;
static my_class* get_instance_ptr(PyObject* self) {
  return &test_my_class;
}

static PyObject* my_class_get_attr(PyObject* unused, PyObject* args) {
  PyObject* self = PyTuple_GetItem(args, 0);
	PyObject* attr = PyTuple_GetItem(args, 1);
	
	my_class* cstruct = get_instance_ptr(self);
	return PyAutoStruct_GetMember(my_class, cstruct, PyString_AsString(attr));
}

static PyObject* my_class_set_attr(PyObject* unused, PyObject* args) {
	PyObject* self = PyTuple_GetItem(args, 0);
	PyObject* attr = PyTuple_GetItem(args, 1);
	PyObject* val = PyTuple_GetItem(args, 2);
	
	my_class* cstruct = get_instance_ptr(self);
	PyAutoStruct_SetMember(my_class, cstruct, PyString_AsString(attr), val);
	Py_RETURN_NONE;
}

static PyMethodDef method_table[] = {
	{"get_attr", my_class_get_attr, METH_VARARGS, ""},
	{"set_attr", my_class_set_attr, METH_VARARGS, ""},
	{NULL, NULL, 0, NULL},
};

int main(int argc, char **argv) {
  
  test_my_class.name = "Hello";
  test_my_class.value = 1.2f;
  
  Py_Initialize();

  PyAutoConvert_RegisterPrimatives();
  PyAutoStruct_Register(my_class);
  PyAutoStruct_RegisterMember(my_class, name, char*);
  PyAutoStruct_RegisterMember(my_class, value, float);
  
  Py_InitModule("my_class", method_table);
  
  PyRun_SimpleString(""
  "import my_class\n"
  "class my_python_class(object):\n"
	"    def __getattr__(self, attr): return my_class.get_attr(self, attr)\n"
	"    def __setattr__(self, attr, val): return my_class.set_attr(self, attr, val)\n"
  "\n"
  "my_class_inst = my_python_class()\n"
  "print my_class_inst.name\n"
  "print my_class_inst.value\n");
  
  Py_Finalize();
  
  return 0;
  
}