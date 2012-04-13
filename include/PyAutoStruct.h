#ifndef PyAutoStruct_h
#define PyAutoStruct_h

#include "Python.h"
#include "PyAutoType.h"

void PyAutoStruct_Initialize(void);
void PyAutoStruct_Finalize(void);

#define PyAutoStruct_Get(type, cstruct, member) PyAutoStruct_GetMember_TypeId(PyTypeId(type), cstruct, #member)
#define PyAutoStruct_GetMember(type, cstruct, member) PyAutoStruct_GetMember_TypeId(PyTypeId(type), cstruct, member)
PyObject* PyAutoStruct_GetMember_TypeId(PyAutoType type, void* cstruct, char* member_name);

#define PyAutoStruct_Set(type, cstruct, member, val) PyAutoStruct_SetMember_TypeId(PyTypeId(type), cstruct, #member, val)
#define PyAutoStruct_SetMember(type, cstruct, member, val) PyAutoStruct_SetMember_TypeId(PyTypeId(type), cstruct, member, val)
PyObject* PyAutoStruct_SetMember_TypeId(PyAutoType type, void* cstruct, char* member, PyObject* val);

#define PyAutoStruct_Register(type) PyAutoStruct_Register_TypeId(PyTypeId(type))
void PyAutoStruct_Register_TypeId(PyAutoType type);

#define PyAutoStruct_RegisterMember(type, member, member_type) PyAutoStruct_RegisterMember_TypeId(PyTypeId(type), #member, PyTypeId(member_type), ((long)&(((type*)0)->member)))
void PyAutoStruct_RegisterMember_TypeId(PyAutoType type, char* member, PyAutoType member_type, int offset);

#endif
