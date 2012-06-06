#ifndef PyAutoFunction_h
#define PyAutoFunction_h

#include "Python.h"
#include "PyAutoType.h"
#include "PyAutoFunctionMacros.h"

void PyAutoFunction_Initialize(void);
void PyAutoFunction_Finalize(void);

PyObject* PyAutoFunction_Call(void* func, PyObject* args);
PyObject* PyAutoFunction_CallByName(char* c_func_name, PyObject* args);

#define PyAutoFunction_Register(func, ret_t, num_args, ...) __VA_ARGS_APPLY__(PyAutoFunction_RegisterArgs##num_args##_Macro, func, ret_t, ##__VA_ARGS__ )
#define PyAutoFunction_RegisterVoid(func, num_args, ...) __VA_ARGS_APPLY__(PyAutoFunction_RegisterArgs##num_args##Void_Macro, func, void, ##__VA_ARGS__ )

typedef void (*PyAutoCFunc)(void*,void*);

void PyAutoFunction_Register_TypeId(void* src_func, PyAutoCFunc ac_func, char* name, PyAutoType ret_tid, int num_args, ...);

#endif
