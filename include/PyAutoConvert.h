#ifndef PyAutoConvert_h
#define PyAutoConvert_h

#include "Python.h"
#include "PyAutoType.h"

void PyAutoConvert_Initialize(void);
void PyAutoConvert_Finalize(void);

#define PyAutoConvert_From(type, c_val) PyAutoConvert_From_TypeId(PyTypeId(type), c_val)
PyObject* PyAutoConvert_From_TypeId(PyAutoType type_id, void* c_val);

#define PyAutoConvert_To(type, py_val, c_out) PyAutoConvert_To_TypeId(PyTypeId(type), py_val, c_out)
void PyAutoConvert_To_TypeId(PyAutoType type_id, PyObject* py_val, void* c_out);

typedef PyObject* (*PyAutoConvert_FromFunc)(void*);
typedef void (*PyAutoConvert_ToFunc)(PyObject*,void*);

#define PyAutoConvert_Register(type, from_func, to_func) PyAutoConvert_Register_TypeId(PyTypeId(type), from_func, to_func);
void PyAutoConvert_Register_TypeId(PyAutoType type_id, PyAutoConvert_FromFunc from_func, PyAutoConvert_ToFunc to_func);

#define PyAutoConvert_RegisterFrom(type, func) PyAutoConvert_RegisterFrom_TypeId(PyTypeId(type), func)
void PyAutoConvert_RegisterFrom_TypeId(PyAutoType type_id, PyAutoConvert_FromFunc func);

#define PyAutoConvert_RegisterTo(type, func) PyAutoConvert_RegisterTo_TypeId(PyTypeId(type), func)
void PyAutoConvert_RegisterTo_TypeId(PyAutoType type_id, PyAutoConvert_ToFunc func);

PyObject* PyAutoConvert_PrimFromChar(void* data);
void PyAutoConvert_PrimToChar(PyObject* pyobj, void* out);
PyObject* PyAutoConvert_PrimFromSignedChar(void* data);
void PyAutoConvert_PrimToSignedChar(PyObject* pyobj, void* out);
PyObject* PyAutoConvert_PrimFromUnsignedChar(void* data);
void PyAutoConvert_PrimToUnsignedChar(PyObject* pyobj, void* out);
PyObject* PyAutoConvert_PrimFromShort(void* data);
void PyAutoConvert_PrimToShort(PyObject* pyobj, void* out);
PyObject* PyAutoConvert_PrimFromUnsignedShort(void* data);
void PyAutoConvert_PrimToUnsignedShort(PyObject* pyobj, void* out);
PyObject* PyAutoConvert_PrimFromInt(void* data);
void PyAutoConvert_PrimToInt(PyObject* pyobj, void* out);
PyObject* PyAutoConvert_PrimFromUnsignedInt(void* data);
void PyAutoConvert_PrimToUnsignedInt(PyObject* pyobj, void* out);
PyObject* PyAutoConvert_PrimFromLong(void* data);
void PyAutoConvert_PrimToLong(PyObject* pyobj, void* out);
PyObject* PyAutoConvert_PrimFromUnsignedLong(void* data);
void PyAutoConvert_PrimToUnsignedLong(PyObject* pyobj, void* out);
PyObject* PyAutoConvert_PrimFromLongLong(void* data);
void PyAutoConvert_PrimToLongLong(PyObject* pyobj, void* out);
PyObject* PyAutoConvert_PrimFromUnsignedLongLong(void* data);
void PyAutoConvert_PrimToUnsignedLongLong(PyObject* pyobj, void* out);
PyObject* PyAutoConvert_PrimFromFloat(void* data);
void PyAutoConvert_PrimToFloat(PyObject* pyobj, void* out);
PyObject* PyAutoConvert_PrimFromDouble(void* data);
void PyAutoConvert_PrimToDouble(PyObject* pyobj, void* out);
PyObject* PyAutoConvert_PrimFromLongDouble(void* data);
void PyAutoConvert_PrimToLongDouble(PyObject* pyobj, void* out);

PyObject* PyAutoConvert_PrimFromCharPtr(void* data);
void PyAutoConvert_PrimToCharPtr(PyObject* pyobj, void* out);
PyObject* PyAutoConvert_PrimFromConstCharPtr(void* data);
void PyAutoConvert_PrimToConstCharPtr(PyObject* pyobj, void* out);

PyObject* PyAutoConvert_PrimFromVoid(void* data);

#endif
