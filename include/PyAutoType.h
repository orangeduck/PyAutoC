#ifndef PyAutoType_h
#define PyAutoType_h

void PyAutoType_Initialize(void);
void PyAutoType_Finalize(void);

typedef int PyAutoType;

#define PyTypeId(type) PyAutoType_Register(#type, sizeof(type))

PyAutoType PyAutoType_Register(char* type, int size);
PyAutoType PyAutoType_Find(char* type);

char* PyAutoType_Name(PyAutoType id);
int PyAutoType_Size(PyAutoType id);

#endif
