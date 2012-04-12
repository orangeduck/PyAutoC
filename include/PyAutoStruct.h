#ifndef PyAutoStruct_h
#define PyAutoStruct_h

#include "Python.h"
#include "PyAutoType.h"

#define PyAutoStruct_Get(type, cstruct, member) PyAutoStruct_GetByName_TypeId(PyTypeId(type), cstruct, PyTypeId(member), ((int)&(((type*)0)->member)))
PyObject* PyAutoStruct_GetByOffset_TypeId(PyAutoType type, void* cstruct, PyAutoType member_type, int offset);

#define PyAutoStruct_GetByName(type, cstruct, member) PyAutoStruct_GetByName_TypeId(PyTypeId(type), cstruct, member)
PyObject* PyAutoStruct_GetByName_TypeId(PyAutoType type, void* cstruct, char* member);

#define PyAutoStruct_Set(type, cstruct, member, val) PyAutoStruct_SetByName_TypeId(PyTypeId(type), cstruct, #member, val)
#define PyAutoStruct_SetByName(type, cstruct, member, val) PyAutoStruct_SetByName_TypeId(PyTypeId(type), cstruct, member, val)
void PyAutoStruct_SetByName_TypeId(PyAutoType type, void* cstruct, char* member, PyObject* val);

#define PyAutoStruct_Register(type) PyAutoStruct_Register_TypeId(PyTypeId(type))
void PyAutoStruct_Register_TypeId(PyAutoType type);

#define PyAutoStruct_RegisterMember(type, member, member_type) PyAutoStruct_RegisterMember_TypeId(PyTypeId(type), #member, PyTypeId(member_type), ((int)&(((type*)0)->member)))
void PyAutoStruct_RegisterMember_TypeId(PyAutoType type, char* member, PyAutoType member_type, int offset);

#endif