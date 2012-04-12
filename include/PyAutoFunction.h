#ifndef PyAutoFunction_h
#define PyAutoFunction_h

#include "Python.h"
#include "PyAutoType.h"
#include "PyAutoFunctionMacros.h"

PyObject* PyAutoFunction_Call(void* c_func, PyObject* args);
PyObject* PyAutoFunction_CallByName(char* c_func_name, PyObject* args);

#define PyAutoFunction_RegisterArgs0(func, ret_t) PyAutoFunction_RegisterArgs0_Macro(func, ret_t)
#define PyAutoFunction_RegisterVoidArgs0(func, ret_t) PyAutoFunction_RegisterVoidArgs0_Macro(func, ret_t)
#define PyAutoFunction_RegisterArgs1(func, ret_t, arg0_t) PyAutoFunction_RegisterArgs1_Macro(func, ret_t, arg0_t) 
#define PyAutoFunction_RegisterVoidArgs1(func, ret_t, arg0_t) PyAutoFunction_RegisterVoidArgs1_Macro(func, ret_t, arg0_t)
#define PyAutoFunction_RegisterArgs2(func, ret_t, arg0_t, arg1_t) PyAutoFunction_RegisterArgs2_Macro(func, ret_t, arg0_t, arg1_t)
#define PyAutoFunction_RegisterVoidArgs2(func, ret_t, arg0_t, arg1_t) PyAutoFunction_RegisterVoidArgs2_Macro(func, ret_t, arg0_t, arg1_t)
#define PyAutoFunction_RegisterArgs3(func, ret_t, arg0_t, arg1_t, arg2_t) PyAutoFunction_RegisterArgs3_Macro(func, ret_t, arg0_t, arg1_t, arg2_t)
#define PyAutoFunction_RegisterVoidArgs3(func, ret_t, arg0_t, arg1_t, arg2_t) PyAutoFunction_RegisterVoidArgs3_Macro(func, ret_t, arg0_t, arg1_t, arg2_t)
#define PyAutoFunction_RegisterArgs4(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t) PyAutoFunction_RegisterArgs4_Macro(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t)
#define PyAutoFunction_RegisterVoidArgs4(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t) PyAutoFunction_RegisterVoidArgs4_Macro(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t)
#define PyAutoFunction_RegisterArgs5(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t) PyAutoFunction_RegisterArgs5_Macro(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t)
#define PyAutoFunction_RegisterVoidArgs5(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t) PyAutoFunction_RegisterVoidArgs5_Macro(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t)

typedef void (*PyAutoCFunc)(void*,void*);

void PyAutoFunction_Register_TypeId(PyAutoCFunc ac_func, void* func, char* name, PyAutoType ret_tid, int num_args, ...);

#endif