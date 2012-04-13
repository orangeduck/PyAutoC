#ifndef PyAutoConvert_h
#define PyAutoConvert_h

#include "Python.h"
#include "PyAutoType.h"

void PyAutoConvert_Initialize();
void PyAutoConvert_Finalize();

#define PyAutoConvert_From(type, c_val) PyAutoConvert_From_TypeId(PyTypeId(type), c_val)
PyObject* PyAutoConvert_From_TypeId(PyAutoType type_id, void* c_val);

#define PyAutoConvert_To(type, py_val, c_out) PyAutoConvert_To_TypeId(PyTypeId(type), py_val, c_out)
PyObject* PyAutoConvert_To_TypeId(PyAutoType type_id, PyObject* py_val, void* c_out);

typedef PyObject* (*PyAutoConvert_FromFunc)(void*);
typedef PyObject* (*PyAutoConvert_ToFunc)(PyObject*,void*);

#define PyAutoConvert_Register(type, from_func, to_func) PyAutoConvert_Register_TypeId(PyTypeId(type), from_func, to_func);
void PyAutoConvert_Register_TypeId(PyAutoType type_id, PyAutoConvert_FromFunc from_func, PyAutoConvert_ToFunc to_func);

#define PyAutoConvert_RegisterFrom(type, func) PyAutoConvert_RegisterFrom_TypeId(PyTypeId(type), func)
void PyAutoConvert_RegisterFrom_TypeId(PyAutoType type_id, PyAutoConvert_FromFunc func);

#define PyAutoConvert_RegisterTo(type, func) PyAutoConvert_RegisterTo_TypeId(PyTypeId(type), func)
void PyAutoConvert_RegisterTo_TypeId(PyAutoType type_id, PyAutoConvert_ToFunc func);

PyObject* PyAutoConvert_PrimFromChar(void* data);
PyObject* PyAutoConvert_PrimToChar(PyObject* pyobj, void* out);
PyObject* PyAutoConvert_PrimFromSignedChar(void* data);
PyObject* PyAutoConvert_PrimToSignedChar(PyObject* pyobj, void* out);
PyObject* PyAutoConvert_PrimFromUnsignedChar(void* data);
PyObject* PyAutoConvert_PrimToUnsignedChar(PyObject* pyobj, void* out);
PyObject* PyAutoConvert_PrimFromShort(void* data);
PyObject* PyAutoConvert_PrimToShort(PyObject* pyobj, void* out);
PyObject* PyAutoConvert_PrimFromUnsignedShort(void* data);
PyObject* PyAutoConvert_PrimToUnsignedShort(PyObject* pyobj, void* out);
PyObject* PyAutoConvert_PrimFromInt(void* data);
PyObject* PyAutoConvert_PrimToInt(PyObject* pyobj, void* out);
PyObject* PyAutoConvert_PrimFromUnsignedInt(void* data);
PyObject* PyAutoConvert_PrimToUnsignedInt(PyObject* pyobj, void* out);
PyObject* PyAutoConvert_PrimFromLong(void* data);
PyObject* PyAutoConvert_PrimToLong(PyObject* pyobj, void* out);
PyObject* PyAutoConvert_PrimFromUnsignedLong(void* data);
PyObject* PyAutoConvert_PrimToUnsignedLong(PyObject* pyobj, void* out);
PyObject* PyAutoConvert_PrimFromLongLong(void* data);
PyObject* PyAutoConvert_PrimToLongLong(PyObject* pyobj, void* out);
PyObject* PyAutoConvert_PrimFromUnsignedLongLong(void* data);
PyObject* PyAutoConvert_PrimToUnsignedLongLong(PyObject* pyobj, void* out);
PyObject* PyAutoConvert_PrimFromFloat(void* data);
PyObject* PyAutoConvert_PrimToFloat(PyObject* pyobj, void* out);
PyObject* PyAutoConvert_PrimFromDouble(void* data);
PyObject* PyAutoConvert_PrimToDouble(PyObject* pyobj, void* out);
PyObject* PyAutoConvert_PrimFromLongDouble(void* data);
PyObject* PyAutoConvert_PrimToLongDouble(PyObject* pyobj, void* out);

PyObject* PyAutoConvert_PrimFromCharPtr(void* data);
PyObject* PyAutoConvert_PrimToCharPtr(PyObject* pyobj, void* out);
PyObject* PyAutoConvert_PrimFromConstCharPtr(void* data);
PyObject* PyAutoConvert_PrimToConstCharPtr(PyObject* pyobj, void* out);

PyObject* PyAutoConvert_PrimFromVoid(void* data);

#endif