#include "PyAutoConvert.h"

static PyAutoConvert_FromFunc* convert_from_funcs;
static PyAutoConvert_ToFunc* convert_to_funcs;

static PyAutoType* convert_from_type_ids;
static PyAutoType* convert_to_type_ids;

static int num_convert_from_funcs = 0;
static int num_reserved_convert_from_funcs = 512;
static int num_convert_to_funcs = 0;
static int num_reserved_convert_to_funcs = 512;

void PyAutoConvert_Initialize() {
  
  convert_from_funcs = malloc(sizeof(PyAutoConvert_FromFunc) * num_reserved_convert_from_funcs);
  convert_to_funcs = malloc(sizeof(PyAutoConvert_ToFunc) * num_reserved_convert_to_funcs);
  convert_from_type_ids = malloc(sizeof(PyAutoType) * num_reserved_convert_from_funcs);
  convert_to_type_ids = malloc(sizeof(PyAutoType) * num_reserved_convert_to_funcs);
  
  PyAutoConvert_Register(char, PyAutoConvert_PrimFromChar, PyAutoConvert_PrimToChar);
  PyAutoConvert_Register(signed char, PyAutoConvert_PrimFromSignedChar, PyAutoConvert_PrimToSignedChar);
  PyAutoConvert_Register(unsigned char, PyAutoConvert_PrimFromUnsignedChar, PyAutoConvert_PrimToUnsignedChar);
  PyAutoConvert_Register(short, PyAutoConvert_PrimFromShort, PyAutoConvert_PrimToShort);
  PyAutoConvert_Register(unsigned short, PyAutoConvert_PrimFromUnsignedShort, PyAutoConvert_PrimToUnsignedShort);
  PyAutoConvert_Register(int, PyAutoConvert_PrimFromInt, PyAutoConvert_PrimToInt);
  PyAutoConvert_Register(unsigned int, PyAutoConvert_PrimFromUnsignedInt, PyAutoConvert_PrimToUnsignedInt);
  PyAutoConvert_Register(long, PyAutoConvert_PrimFromLong, PyAutoConvert_PrimToLong);
  PyAutoConvert_Register(unsigned long, PyAutoConvert_PrimFromUnsignedLong, PyAutoConvert_PrimToUnsignedLong);
  PyAutoConvert_Register(long long, PyAutoConvert_PrimFromLongLong, PyAutoConvert_PrimToLongLong);
  PyAutoConvert_Register(unsigned long long, PyAutoConvert_PrimFromUnsignedLongLong, PyAutoConvert_PrimToUnsignedLongLong);
  PyAutoConvert_Register(float, PyAutoConvert_PrimFromFloat, PyAutoConvert_PrimToFloat);
  PyAutoConvert_Register(double, PyAutoConvert_PrimFromDouble, PyAutoConvert_PrimToDouble);
  PyAutoConvert_Register(long double, PyAutoConvert_PrimFromLongDouble, PyAutoConvert_PrimToLongDouble);
  
  PyAutoConvert_Register(char*, PyAutoConvert_PrimFromCharPtr, PyAutoConvert_PrimToCharPtr);
  PyAutoConvert_Register(const char*, PyAutoConvert_PrimFromConstCharPtr, PyAutoConvert_PrimToConstCharPtr);
  
  PyAutoConvert_RegisterFrom(void, PyAutoConvert_PrimFromVoid);
  
}

void PyAutoConvert_Finalize() {
  
  free(convert_from_funcs);
  free(convert_to_funcs);
  
}

PyObject* PyAutoConvert_From_TypeId(PyAutoType type_id, void* c_val) {
  
  for(int i = num_convert_from_funcs-1; i >= 0; i--) {
    if (type_id == convert_from_type_ids[i]) {
      return convert_from_funcs[i](c_val);
    }
  }
  
  PyErr_Format(PyExc_TypeError, "Conversion to PyObject from type '%s' not registered!", PyAutoType_Name(type_id));
  return NULL;
  
}

PyObject* PyAutoConvert_To_TypeId(PyAutoType type_id, PyObject* py_val, void* c_out) {

  for(int i = num_convert_to_funcs-1; i >= 0; i--) {
    if (type_id == convert_to_type_ids[i]) {
      return convert_to_funcs[i](py_val, c_out);
    }
  }
  
  PyErr_Format(PyExc_TypeError, "Conversion from PyObject to type '%s' not registered!", PyAutoType_Name(type_id));
  return NULL;
  
}

void PyAutoConvert_Register_TypeId(PyAutoType type_id, PyAutoConvert_FromFunc from_func, PyAutoConvert_ToFunc to_func) {
  
  if (num_convert_from_funcs >= num_reserved_convert_from_funcs) {
    num_reserved_convert_from_funcs += 512;
    convert_from_funcs = realloc(convert_from_funcs, sizeof(PyAutoConvert_FromFunc) * num_reserved_convert_from_funcs);
    convert_from_type_ids = realloc(convert_from_type_ids, sizeof(PyAutoType) * num_reserved_convert_from_funcs);
  }
  if (num_convert_to_funcs >= num_reserved_convert_to_funcs) {
    num_reserved_convert_to_funcs += 512;
    convert_to_funcs = realloc(convert_to_funcs, sizeof(PyAutoConvert_ToFunc) * num_reserved_convert_to_funcs);
    convert_to_type_ids = realloc(convert_to_type_ids, sizeof(PyAutoType) * num_reserved_convert_to_funcs);
  }

  convert_from_funcs[num_convert_from_funcs] = from_func;
  convert_from_type_ids[num_convert_from_funcs] = type_id;
  num_convert_from_funcs++;
  
  convert_to_funcs[num_convert_to_funcs] = to_func;
  convert_to_type_ids[num_convert_to_funcs] = type_id;
  num_convert_to_funcs++;
  
}

void PyAutoConvert_RegisterFrom_TypeId(PyAutoType type_id, PyAutoConvert_FromFunc func) {
  
  if (num_convert_from_funcs >= num_reserved_convert_from_funcs) {
    num_reserved_convert_from_funcs += 512;
    convert_from_funcs = realloc(convert_from_funcs, sizeof(PyAutoConvert_FromFunc) * num_reserved_convert_from_funcs);
    convert_from_type_ids = realloc(convert_from_type_ids, sizeof(PyAutoType) * num_reserved_convert_from_funcs);
  }
  
  convert_from_funcs[num_convert_from_funcs] = func;
  convert_from_type_ids[num_convert_from_funcs] = type_id;
  num_convert_from_funcs++;
  
}

void PyAutoConvert_RegisterTo_TypeId(PyAutoType type_id, PyAutoConvert_ToFunc func) {
  
  if (num_convert_to_funcs >= num_reserved_convert_to_funcs) {
    num_reserved_convert_to_funcs += 512;
    convert_to_funcs = realloc(convert_to_funcs, sizeof(PyAutoConvert_ToFunc) * num_reserved_convert_to_funcs);
    convert_to_type_ids = realloc(convert_to_type_ids, sizeof(PyAutoType) * num_reserved_convert_to_funcs);
  }
  
  convert_to_funcs[num_convert_to_funcs] = func;
  convert_to_type_ids[num_convert_to_funcs] = type_id;
  num_convert_to_funcs++;
  
}

PyObject* PyAutoConvert_PrimFromChar(void* data) {
  return Py_BuildValue("c", data);
}
PyObject* PyAutoConvert_PrimToChar(PyObject* pyobj, void* out) {
  char* c = PyString_AsString(pyobj);
  if (PyErr_Occurred()) {
    return NULL;
  } else {
    *(char*)out = c[0];
    Py_RETURN_NONE;
  }
}
PyObject* PyAutoConvert_PrimFromSignedChar(void* data) {
  return Py_BuildValue("c", data);
}
PyObject* PyAutoConvert_PrimToSignedChar(PyObject* pyobj, void* out) {
  char* c = PyString_AsString(pyobj);
  if (PyErr_Occurred()) {
    return NULL;
  } else {
    *(char*)out = c[0];
    Py_RETURN_NONE;
  }
}
PyObject* PyAutoConvert_PrimFromUnsignedChar(void* data) {
  return Py_BuildValue("c", data);
}
PyObject* PyAutoConvert_PrimToUnsignedChar(PyObject* pyobj, void* out) {
  char* c = PyString_AsString(pyobj);
  if (PyErr_Occurred()) {
    return NULL;
  } else {
    *(char*)out = c[0];
    Py_RETURN_NONE;
  }
}
PyObject* PyAutoConvert_PrimFromShort(void* data) {
  return PyInt_FromLong(*(short*)data);
}
PyObject* PyAutoConvert_PrimToShort(PyObject* pyobj, void* out) {
  short data = PyInt_AsLong(pyobj);
  if (PyErr_Occurred()) {
    return NULL;
  } else {
    *(short*)out = data;
    Py_RETURN_NONE;
  }
}
PyObject* PyAutoConvert_PrimFromUnsignedShort(void* data) {
  return PyInt_FromLong(*(unsigned short*)data);
}
PyObject* PyAutoConvert_PrimToUnsignedShort(PyObject* pyobj, void* out) {
  unsigned short data = PyInt_AsLong(pyobj);
  if (PyErr_Occurred()) {
    return NULL;
  } else {
    *(unsigned short*)out = data;
    Py_RETURN_NONE;
  }  
}
PyObject* PyAutoConvert_PrimFromInt(void* data) {
  return PyInt_FromLong(*(int*)data);
}
PyObject* PyAutoConvert_PrimToInt(PyObject* pyobj, void* out) {
  int data = PyInt_AsLong(pyobj);
  if (PyErr_Occurred()) {
    return NULL;
  } else {
    *(int*)out = data;
    Py_RETURN_NONE;
  }
}
PyObject* PyAutoConvert_PrimFromUnsignedInt(void* data) {
  return PyInt_FromLong(*(unsigned int*)data);
}
PyObject* PyAutoConvert_PrimToUnsignedInt(PyObject* pyobj, void* out) {
  unsigned int data = PyInt_AsLong(pyobj);
  if (PyErr_Occurred()) {
    return NULL;
  } else {
    *(unsigned int*)out = data;
    Py_RETURN_NONE;
  }
}
PyObject* PyAutoConvert_PrimFromLong(void* data) {
  return PyLong_FromLong(*(long*)data);
}
PyObject* PyAutoConvert_PrimToLong(PyObject* pyobj, void* out) {
  long data = PyLong_AsLong(pyobj);
  if (PyErr_Occurred()) {
    return NULL;
  } else {
    *(long*)out = data;
    Py_RETURN_NONE;
  }
}
PyObject* PyAutoConvert_PrimFromUnsignedLong(void* data) {
  return PyLong_FromUnsignedLong(*(unsigned long*)data);
}
PyObject* PyAutoConvert_PrimToUnsignedLong(PyObject* pyobj, void* out) {
  unsigned long data = PyLong_AsUnsignedLong(pyobj);
  if (PyErr_Occurred()) {
    return NULL;
  } else {
    *(unsigned long*)out = data;
    Py_RETURN_NONE;
  }
}
PyObject* PyAutoConvert_PrimFromLongLong(void* data) {
  return PyLong_FromLongLong(*(long long*)data);
}
PyObject* PyAutoConvert_PrimToLongLong(PyObject* pyobj, void* out) {
  long long data = PyLong_AsLongLong(pyobj);
  if (PyErr_Occurred()) {
    return NULL;
  } else {
    *(long long*)out = data;
    Py_RETURN_NONE;
  }
}
PyObject* PyAutoConvert_PrimFromUnsignedLongLong(void* data) {
  return PyLong_FromUnsignedLongLong(*(unsigned long long*)data);
}
PyObject* PyAutoConvert_PrimToUnsignedLongLong(PyObject* pyobj, void* out) {
  unsigned long long data = PyLong_AsUnsignedLongLong(pyobj);
  if (PyErr_Occurred()) {
    return NULL;
  } else {
    *(unsigned long long*)out = data;
    Py_RETURN_NONE;
  }
}
PyObject* PyAutoConvert_PrimFromFloat(void* data) {
  return PyFloat_FromDouble(*(float*)data);
}
PyObject* PyAutoConvert_PrimToFloat(PyObject* pyobj, void* out) {
  float data = PyFloat_AsDouble(pyobj);
  if (PyErr_Occurred()) {
    return NULL;
  } else {
    *(float*)out = data;
    Py_RETURN_NONE;
  }
}
PyObject* PyAutoConvert_PrimFromDouble(void* data) {
  return PyFloat_FromDouble(*(double*)data);  
}
PyObject* PyAutoConvert_PrimToDouble(PyObject* pyobj, void* out) {
  double data = PyFloat_AsDouble(pyobj);
  if (PyErr_Occurred()) {
    return NULL;
  } else {
    *(double*)out = data;
    Py_RETURN_NONE;
  }
}
PyObject* PyAutoConvert_PrimFromLongDouble(void* data) {
  return PyFloat_FromDouble(*(long double*)data);  
}
PyObject* PyAutoConvert_PrimToLongDouble(PyObject* pyobj, void* out) {
  long double data = PyFloat_AsDouble(pyobj);
  if (PyErr_Occurred()) {
    return NULL;
  } else {
    *(long double*)out = data;
    Py_RETURN_NONE;
  }
}

PyObject* PyAutoConvert_PrimFromCharPtr(void* data) {
  return PyString_FromString(*(char**)data);
}
PyObject* PyAutoConvert_PrimToCharPtr(PyObject* pyobj, void* out) {
  char* data = PyString_AsString(pyobj);
  if (PyErr_Occurred()) {
    return NULL;
  } else {
    *(char**)out = data;
    Py_RETURN_NONE;
  }
}
PyObject* PyAutoConvert_PrimFromConstCharPtr(void* data) {
  return PyString_FromString(*(const char**)data);
}
PyObject* PyAutoConvert_PrimToConstCharPtr(PyObject* pyobj, void* out) {
  const char* data = PyString_AsString(pyobj);
  if (PyErr_Occurred()) {
    return NULL;
  } else {
    *(const char**)out = data;
    Py_RETURN_NONE;
  }
}

PyObject* PyAutoConvert_PrimFromVoid(void* data) {
  Py_RETURN_NONE;
}
