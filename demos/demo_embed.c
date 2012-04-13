#include "Python.h"
#include "PyAutoC.h"

typedef struct {
  char* name;
  int num_wings;
} birdie;

static birdie test_birdie;
static birdie* get_instance_ptr(PyObject* self) {
  return &test_birdie;
}

static PyObject* birdie_get_attr(PyObject* unused, PyObject* args) {
  PyObject* self = PyTuple_GetItem(args, 0);
	PyObject* attr = PyTuple_GetItem(args, 1);
	
	birdie* bird = get_instance_ptr(self);
	return PyAutoStruct_GetMember(birdie, bird, PyString_AsString(attr));
}

static PyObject* birdie_set_attr(PyObject* unused, PyObject* args) {
	PyObject* self = PyTuple_GetItem(args, 0);
	PyObject* attr = PyTuple_GetItem(args, 1);
	PyObject* val = PyTuple_GetItem(args, 2);
	
	birdie* bird = get_instance_ptr(self);
	return PyAutoStruct_SetMember(birdie, bird, PyString_AsString(attr), val);
}

static PyMethodDef method_table[] = {
	{"get_attr", birdie_get_attr, METH_VARARGS, ""},
	{"set_attr", birdie_set_attr, METH_VARARGS, ""},
	{NULL, NULL, 0, NULL},
};

int main(int argc, char **argv) {
  
  test_birdie.name = "MrFlingly";
  test_birdie.num_wings = 2;
  
  Py_Initialize();
  PyAutoC_Initialize();
  
  PyAutoStruct_Register(birdie);
  PyAutoStruct_RegisterMember(birdie, name, char*);
  PyAutoStruct_RegisterMember(birdie, num_wings, int);
  
  Py_InitModule("birdie", method_table);
  
  PyRun_SimpleString(""
  "import birdie\n"
  "class python_birdie(object):\n"
	"    def __getattr__(self, attr): return birdie.get_attr(self, attr)\n"
	"    def __setattr__(self, attr, val): return birdie.set_attr(self, attr, val)\n"
  "\n"
  "bird = python_birdie()\n"
  "print bird.name\n"
  "print bird.num_wings\n");
  
  PyAutoC_Finalize();
  Py_Finalize();
  
  return 0;
  
}