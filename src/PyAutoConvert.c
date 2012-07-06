#include "PyAutoC.h"

static PyAutoHashtable* convert_from_table;
static PyAutoHashtable* convert_to_table;

void PyAutoConvert_Initialize(void) {
  
  convert_from_table = PyAutoHashtable_New(256);
  convert_to_table = PyAutoHashtable_New(256);
  
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

void PyAutoConvert_Finalize(void) {
  
  PyAutoHashtable_Delete(convert_from_table);
  PyAutoHashtable_Delete(convert_to_table);
  
}

PyObject* PyAutoConvert_From_TypeId(PyAutoType type_id, void* c_val) {
  
  PyAutoConvert_FromFunc convert_from_func = PyAutoHashtable_Get(convert_from_table, PyAutoType_Name(type_id));
  if (convert_from_func != NULL) {
    return convert_from_func(c_val);
  }
  
  if (PyAutoStruct_IsRegistered_TypeId(type_id)) {
    return PyAutoStruct_Convert_From_TypeId(type_id, c_val);
  }
  
  return PyErr_Format(PyExc_TypeError, "PyAutoConvert: Conversion to PyObject from type '%s' not registered!", PyAutoType_Name(type_id));
  
}

void PyAutoConvert_To_TypeId(PyAutoType type_id, PyObject* py_val, void* c_out) {
  
  PyAutoConvert_ToFunc convert_to_func = PyAutoHashtable_Get(convert_to_table, PyAutoType_Name(type_id));
  if (convert_to_func != NULL) {
    return convert_to_func(py_val, c_out);
  }
  
  if (PyAutoStruct_IsRegistered_TypeId(type_id)) {
    return PyAutoStruct_Convert_To_TypeId(type_id, py_val, c_out);
  }
  
  PyErr_Format(PyExc_TypeError, "PyAutoConvert: Conversion from PyObject to type '%s' not registered!", PyAutoType_Name(type_id));
  
}

void PyAutoConvert_Register_TypeId(PyAutoType type_id, PyAutoConvert_FromFunc from_func, PyAutoConvert_ToFunc to_func) {
  
  PyAutoHashtable_Set(convert_from_table, PyAutoType_Name(type_id), from_func);
  PyAutoHashtable_Set(convert_to_table, PyAutoType_Name(type_id), to_func);
  
}

void PyAutoConvert_RegisterFrom_TypeId(PyAutoType type_id, PyAutoConvert_FromFunc func) {

  PyAutoHashtable_Set(convert_from_table, PyAutoType_Name(type_id), func);
  
}

void PyAutoConvert_RegisterTo_TypeId(PyAutoType type_id, PyAutoConvert_ToFunc func) {
  
  PyAutoHashtable_Set(convert_to_table, PyAutoType_Name(type_id), func);
  
}

PyObject* PyAutoConvert_PrimFromChar(void* data) {
  return Py_BuildValue("c", data);
}
void PyAutoConvert_PrimToChar(PyObject* pyobj, void* out) {
  char* c = PyString_AsString(pyobj);
  *(char*)out = c[0];
}
PyObject* PyAutoConvert_PrimFromSignedChar(void* data) {
  return Py_BuildValue("c", data);
}
void PyAutoConvert_PrimToSignedChar(PyObject* pyobj, void* out) {
  char* c = PyString_AsString(pyobj);
  *(char*)out = c[0];
}
PyObject* PyAutoConvert_PrimFromUnsignedChar(void* data) {
  return Py_BuildValue("c", data);
}
void PyAutoConvert_PrimToUnsignedChar(PyObject* pyobj, void* out) {
  char* c = PyString_AsString(pyobj);
  *(char*)out = c[0];
}
PyObject* PyAutoConvert_PrimFromShort(void* data) {
  return PyInt_FromLong(*(short*)data);
}
void PyAutoConvert_PrimToShort(PyObject* pyobj, void* out) {
  short data = PyInt_AsLong(pyobj);
  *(short*)out = data;
}
PyObject* PyAutoConvert_PrimFromUnsignedShort(void* data) {
  return PyInt_FromLong(*(unsigned short*)data);
}
void PyAutoConvert_PrimToUnsignedShort(PyObject* pyobj, void* out) {
  unsigned short data = PyInt_AsLong(pyobj);
  *(unsigned short*)out = data;
}
PyObject* PyAutoConvert_PrimFromInt(void* data) {
  return PyInt_FromLong(*(int*)data);
}
void PyAutoConvert_PrimToInt(PyObject* pyobj, void* out) {
  int data = PyInt_AsLong(pyobj);
  *(int*)out = data;
}
PyObject* PyAutoConvert_PrimFromUnsignedInt(void* data) {
  return PyInt_FromLong(*(unsigned int*)data);
}
void PyAutoConvert_PrimToUnsignedInt(PyObject* pyobj, void* out) {
  unsigned int data = PyInt_AsLong(pyobj);
  *(unsigned int*)out = data;
}
PyObject* PyAutoConvert_PrimFromLong(void* data) {
  return PyLong_FromLong(*(long*)data);
}
void PyAutoConvert_PrimToLong(PyObject* pyobj, void* out) {
  long data = PyLong_AsLong(pyobj);
  *(long*)out = data;
}
PyObject* PyAutoConvert_PrimFromUnsignedLong(void* data) {
  return PyLong_FromUnsignedLong(*(unsigned long*)data);
}
void PyAutoConvert_PrimToUnsignedLong(PyObject* pyobj, void* out) {
  unsigned long data = PyLong_AsUnsignedLong(pyobj);
  *(unsigned long*)out = data;
}
PyObject* PyAutoConvert_PrimFromLongLong(void* data) {
  return PyLong_FromLongLong(*(long long*)data);
}
void PyAutoConvert_PrimToLongLong(PyObject* pyobj, void* out) {
  long long data = PyLong_AsLongLong(pyobj);
  *(long long*)out = data;
}
PyObject* PyAutoConvert_PrimFromUnsignedLongLong(void* data) {
  return PyLong_FromUnsignedLongLong(*(unsigned long long*)data);
}
void PyAutoConvert_PrimToUnsignedLongLong(PyObject* pyobj, void* out) {
  unsigned long long data = PyLong_AsUnsignedLongLong(pyobj);
  *(unsigned long long*)out = data;
}
PyObject* PyAutoConvert_PrimFromFloat(void* data) {
  return PyFloat_FromDouble(*(float*)data);
}
void PyAutoConvert_PrimToFloat(PyObject* pyobj, void* out) {
  float data = PyFloat_AsDouble(pyobj);
  *(float*)out = data;
}
PyObject* PyAutoConvert_PrimFromDouble(void* data) {
  return PyFloat_FromDouble(*(double*)data);  
}
void PyAutoConvert_PrimToDouble(PyObject* pyobj, void* out) {
  double data = PyFloat_AsDouble(pyobj);
  *(double*)out = data;
}
PyObject* PyAutoConvert_PrimFromLongDouble(void* data) {
  return PyFloat_FromDouble(*(long double*)data);  
}
void PyAutoConvert_PrimToLongDouble(PyObject* pyobj, void* out) {
  long double data = PyFloat_AsDouble(pyobj);
  *(long double*)out = data;
}

PyObject* PyAutoConvert_PrimFromCharPtr(void* data) {
  return PyString_FromString(*(char**)data);
}
void PyAutoConvert_PrimToCharPtr(PyObject* pyobj, void* out) {
  char* data = PyString_AsString(pyobj);
  *(char**)out = data;
}
PyObject* PyAutoConvert_PrimFromConstCharPtr(void* data) {
  return PyString_FromString(*(const char**)data);
}
void PyAutoConvert_PrimToConstCharPtr(PyObject* pyobj, void* out) {
  const char* data = PyString_AsString(pyobj);
  *(const char**)out = data;
}

PyObject* PyAutoConvert_PrimFromVoid(void* data) {
  Py_RETURN_NONE;
}
