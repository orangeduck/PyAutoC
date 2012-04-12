#include "Python.h"
#include "PyAutoC.h"

typedef struct {
  float x, y, z;
} vector3;

int main(int argc, char **argv) {
	
	Py_Initialize();
	
	PyAutoConvert_RegisterPrimatives();
	
	PyAutoStruct_Register(vector3);
	PyAutoStruct_RegisterMember(vector3, x, float);
	PyAutoStruct_RegisterMember(vector3, y, float);
	PyAutoStruct_RegisterMember(vector3, z, float);

	vector3 position = {1.0f, 2.11f, 3.16f};

	PyObject* y = PyAutoStruct_Get(vector3, &position, y);
	//PyObject_Print(y, stdout, 0);
	
	Py_DECREF(y);
	Py_Finalize();
	
	return 0;
}