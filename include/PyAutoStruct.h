#ifndef PyAutoStruct_h
#define PyAutoStruct_h

#include "Python.h"
#include "PyAutoType.h"

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

#endif
