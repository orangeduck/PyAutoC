#ifndef PyAutoType_h
#define PyAutoType_h

typedef int PyAutoType;

#define PyTypeId(type) PyAutoType_Register(#type, sizeof(type))

PyAutoType PyAutoType_Register(const char* type, int size);

const char* PyAutoType_Name(PyAutoType id);
int PyAutoType_Size(PyAutoType id);

#endif
