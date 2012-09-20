#include "Python.h"
#include "PyAutoC.h"

typedef struct {
    int x, y;
} pair;

static PyObject* convert_from_pair(const void* data) {
    pair p = *(pair*)data;
    return Py_BuildValue("(ii)", p.x, p.y);
}

static void convert_to_pair(PyObject* pyobj, void* out) {
    pair* p = (pair*)out;
    p->x = PyInt_AsLong(PyTuple_GetItem(pyobj, 0));
    p->y = PyInt_AsLong(PyTuple_GetItem(pyobj, 1));
}

typedef struct {
  char* first_name;
  char* second_name;
  float coolness;
} person_details;

int main(int argc, char **argv) {
	
	Py_Initialize();
	PyAutoC_Initialize();
	
	PyAutoConvert_Register(pair, convert_from_pair, convert_to_pair);
	
  pair p = {1, 2};
  PyObject* pypair = PyAutoConvert_From(pair, &p);
	PyObject_Print(pypair, stdout, 0);
	Py_DECREF(pypair);
	
  PyAutoStruct_Register(person_details);
  PyAutoStruct_RegisterMember(person_details, first_name, char*);
  PyAutoStruct_RegisterMember(person_details, second_name, char*);
  PyAutoStruct_RegisterMember(person_details, coolness, float);

  person_details my_details = {"Daniel", "Holden", 125212.213};
  PyObject* py_details = PyAutoConvert_From(person_details, &my_details);
  PyObject* py_first_name = PyObject_GetAttrString(py_details, "first_name");
  PyObject_Print(py_first_name, stdout, 0);
	
	Py_DECREF(py_first_name);
	Py_DECREF(py_details);
  
	PyAutoC_Finalize();
	Py_Finalize();
	
	return 0;
}
