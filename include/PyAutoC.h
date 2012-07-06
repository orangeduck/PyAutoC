/*
** PyAutoC - Automatically Wrap C Structs and Functions at runtime for the Python/C API
** https://github.com/orangeduck/PyAutoC
** Daniel Holden - contact@daniel-holden.com
** Licensed under BSD
*/

#ifndef PyAutoC_h
#define PyAutoC_h

#include "Python.h"

/*
** Init Functions
*/

void PyAutoC_Initialize(void);
void PyAutoC_Finalize(void);


/*
** Type Recording
*/

void PyAutoType_Initialize(void);
void PyAutoType_Finalize(void);

typedef int PyAutoType;

#define PyTypeId(type) PyAutoType_Register(#type, sizeof(type))

PyAutoType PyAutoType_Register(char* type, int size);
PyAutoType PyAutoType_Find(char* type);

char* PyAutoType_Name(PyAutoType id);
int PyAutoType_Size(PyAutoType id);


/*
** Conversion Functions
*/

void PyAutoConvert_Initialize(void);
void PyAutoConvert_Finalize(void);

#define PyAutoConvert_From(type, c_val) PyAutoConvert_From_TypeId(PyTypeId(type), c_val)
#define PyAutoConvert_To(type, py_val, c_out) PyAutoConvert_To_TypeId(PyTypeId(type), py_val, c_out)

PyObject* PyAutoConvert_From_TypeId(PyAutoType type_id, void* c_val);
void PyAutoConvert_To_TypeId(PyAutoType type_id, PyObject* py_val, void* c_out);

typedef PyObject* (*PyAutoConvert_FromFunc)(void*);
typedef void (*PyAutoConvert_ToFunc)(PyObject*,void*);

#define PyAutoConvert_Register(type, from_func, to_func) PyAutoConvert_Register_TypeId(PyTypeId(type), from_func, to_func);
#define PyAutoConvert_RegisterFrom(type, func) PyAutoConvert_RegisterFrom_TypeId(PyTypeId(type), func)
#define PyAutoConvert_RegisterTo(type, func) PyAutoConvert_RegisterTo_TypeId(PyTypeId(type), func)

void PyAutoConvert_Register_TypeId(PyAutoType type_id, PyAutoConvert_FromFunc from_func, PyAutoConvert_ToFunc to_func);
void PyAutoConvert_RegisterFrom_TypeId(PyAutoType type_id, PyAutoConvert_FromFunc func);
void PyAutoConvert_RegisterTo_TypeId(PyAutoType type_id, PyAutoConvert_ToFunc func);

PyObject* PyAutoConvert_PrimFromChar(void* data);
PyObject* PyAutoConvert_PrimFromSignedChar(void* data);
PyObject* PyAutoConvert_PrimFromUnsignedChar(void* data);
PyObject* PyAutoConvert_PrimFromShort(void* data);
PyObject* PyAutoConvert_PrimFromUnsignedShort(void* data);
PyObject* PyAutoConvert_PrimFromInt(void* data);
PyObject* PyAutoConvert_PrimFromUnsignedInt(void* data);
PyObject* PyAutoConvert_PrimFromLong(void* data);
PyObject* PyAutoConvert_PrimFromUnsignedLong(void* data);
PyObject* PyAutoConvert_PrimFromLongLong(void* data);
PyObject* PyAutoConvert_PrimFromUnsignedLongLong(void* data);
PyObject* PyAutoConvert_PrimFromFloat(void* data);
PyObject* PyAutoConvert_PrimFromDouble(void* data);
PyObject* PyAutoConvert_PrimFromLongDouble(void* data);
PyObject* PyAutoConvert_PrimFromCharPtr(void* data);
PyObject* PyAutoConvert_PrimFromConstCharPtr(void* data);
PyObject* PyAutoConvert_PrimFromVoid(void* data);

void PyAutoConvert_PrimToChar(PyObject* pyobj, void* out);
void PyAutoConvert_PrimToSignedChar(PyObject* pyobj, void* out);
void PyAutoConvert_PrimToUnsignedChar(PyObject* pyobj, void* out);
void PyAutoConvert_PrimToShort(PyObject* pyobj, void* out);
void PyAutoConvert_PrimToUnsignedShort(PyObject* pyobj, void* out);
void PyAutoConvert_PrimToInt(PyObject* pyobj, void* out);
void PyAutoConvert_PrimToUnsignedInt(PyObject* pyobj, void* out);
void PyAutoConvert_PrimToLong(PyObject* pyobj, void* out);
void PyAutoConvert_PrimToUnsignedLong(PyObject* pyobj, void* out);
void PyAutoConvert_PrimToLongLong(PyObject* pyobj, void* out);
void PyAutoConvert_PrimToUnsignedLongLong(PyObject* pyobj, void* out);
void PyAutoConvert_PrimToFloat(PyObject* pyobj, void* out);
void PyAutoConvert_PrimToDouble(PyObject* pyobj, void* out);
void PyAutoConvert_PrimToLongDouble(PyObject* pyobj, void* out);
void PyAutoConvert_PrimToCharPtr(PyObject* pyobj, void* out);
void PyAutoConvert_PrimToConstCharPtr(PyObject* pyobj, void* out);


/*
** Struct Recording
*/

void PyAutoStruct_Initialize(void);
void PyAutoStruct_Finalize(void);

#define PyAutoStruct_Offset(type, member) ((long)&(((type*)0)->member))

#define PyAutoStruct_Get(type, cstruct, member) PyAutoStruct_Get_TypeId(PyTypeId(type), cstruct, PyAutoStruct_Offset(type, member))
#define PyAutoStruct_Set(type, cstruct, member, val) PyAutoStruct_Set_TypeId(PyTypeId(type), cstruct, PyAutoStruct_Offset(type, member), val)
#define PyAutoStruct_Has(type, member) PyAutoStruct_Has_TypeId(PyTypeId(type), PyAutoStruct_Offset(type, member))

#define PyAutoStruct_GetMember(type, cstruct, member) PyAutoStruct_GetMember_TypeId(PyTypeId(type), cstruct, member)
#define PyAutoStruct_SetMember(type, cstruct, member, val) PyAutoStruct_SetMember_TypeId(PyTypeId(type), cstruct, member, val)
#define PyAutoStruct_HasMember(type, member) PyAutoStruct_HasMember_TypeId(PyTypeId(type), member)

PyObject* PyAutoStruct_Get_TypeId(PyAutoType type, void* cstruct, int offset);
PyObject* PyAutoStruct_Set_TypeId(PyAutoType type, void* cstruct, int offset, PyObject* val);
int PyAutoStruct_Has_TypeId(PyAutoType type, int offset);

PyObject* PyAutoStruct_GetMember_TypeId(PyAutoType type, void* cstruct, char* member);
PyObject* PyAutoStruct_SetMember_TypeId(PyAutoType type, void* cstruct, char* member, PyObject* val);
int PyAutoStruct_HasMember_TypeId(PyAutoType type,  char* member);

#define PyAutoStruct_Register(type) PyAutoStruct_Register_TypeId(PyTypeId(type))
#define PyAutoStruct_RegisterMember(type, member, member_type) PyAutoStruct_RegisterMember_TypeId(PyTypeId(type), #member, PyTypeId(member_type), PyAutoStruct_Offset(type, member))

#define PyAutoStruct_IsRegistered(type) PyAutoStruct_IsRegistered_TypeId(PyTypeId(type))

void PyAutoStruct_Register_TypeId(PyAutoType type);
void PyAutoStruct_RegisterMember_TypeId(PyAutoType type, char* member, PyAutoType member_type, int offset);

int PyAutoStruct_IsRegistered_TypeId(PyAutoType type);

#define PyAutoStruct_Convert_From(type, cstruct) PyAutoStruct_Convert_TypeId(PyTypeId(type), cstruct)
#define PyAutoStruct_Convert_To(type, pyobj, out) PyAutoStruct_Convert_To_TypeId(PyTypeId(type), pyobj, out)

PyObject* PyAutoStruct_Convert_From_TypeId(PyAutoType type, void* cstruct);
void PyAutoStruct_Convert_To_TypeId(PyAutoType type, PyObject* pyobj, void* out);


/*
** Function Recording
*/

#include "PyAutoFunctionMacros.h"

void PyAutoFunction_Initialize(void);
void PyAutoFunction_Finalize(void);

PyObject* PyAutoFunction_Call(void* func, PyObject* args);
PyObject* PyAutoFunction_CallByName(char* c_func_name, PyObject* args);

#define PyAutoFunction_Register(func, ret_t, num_args, ...) __VA_ARGS_APPLY__(PyAutoFunction_RegisterArgs##num_args##_Macro, func, ret_t, ##__VA_ARGS__ )
#define PyAutoFunction_RegisterVoid(func, num_args, ...) __VA_ARGS_APPLY__(PyAutoFunction_RegisterArgs##num_args##Void_Macro, func, void, ##__VA_ARGS__ )

typedef void (*PyAutoCFunc)(void*,void*);

void PyAutoFunction_Register_TypeId(void* src_func, PyAutoCFunc ac_func, char* name, PyAutoType ret_tid, int num_args, ...);


/*
** Internal Hashtable Untility
*/

typedef struct PyAutoBucket {
  void* item;
  char* string;
  struct PyAutoBucket* next;
  struct PyAutoBucket* prev;
} PyAutoBucket;

typedef struct {
  PyAutoBucket** buckets;
  int size;
} PyAutoHashtable;

PyAutoHashtable* PyAutoHashtable_New(int table_size);
void PyAutoHashtable_Delete(PyAutoHashtable* ht);

int PyAutoHashtable_Contains(PyAutoHashtable* ht, char* string);
void* PyAutoHashtable_Get(PyAutoHashtable* ht, char* string);
void PyAutoHashtable_Set(PyAutoHashtable* ht, char* string, void* item);

char* PyAutoHashtable_Find(PyAutoHashtable* ht, void* item);

void PyAutoHashtable_Map(PyAutoHashtable* ht, void (*func)(void*));

#endif
