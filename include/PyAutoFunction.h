#ifndef PyAutoFunction_h
#define PyAutoFunction_h

#include "Python.h"
#include "PyAutoType.h"
#include "PyAutoFunctionMacros.h"

PyObject* PyAutoFunc_Call(void* c_func, PyObject* args);
PyObject* PyAutoFunc_CallByName(char* c_func_name, PyObject* args);

#define PyAutoFunc_Register_Args0(func, ret_t) PyAutoFunc_Register_Args0_Macro(func, ret_t)
#define PyAutoFunc_Register_Void_Args0(func, ret_t) PyAutoFunc_Register_Void_Args0_Macro(func, ret_t)
#define PyAutoFunc_Register_Args1(func, ret_t, arg0_t) PyAutoFunc_Register_Args1_Macro(func, ret_t, arg0_t) 
#define PyAutoFunc_Register_Void_Args1(func, ret_t, arg0_t) PyAutoFunc_Register_Void_Args1_Macro(func, ret_t, arg0_t)
#define PyAutoFunc_Register_Args2(func, ret_t, arg0_t, arg1_t) PyAutoFunc_Register_Args2_Macro(func, ret_t, arg0_t, arg1_t)
#define PyAutoFunc_Register_Void_Args2(func, ret_t, arg0_t, arg1_t) PyAutoFunc_Register_Void_Args2_Macro(func, ret_t, arg0_t, arg1_t)
#define PyAutoFunc_Register_Args3(func, ret_t, arg0_t, arg1_t, arg2_t) PyAutoFunc_Register_Args3_Macro(func, ret_t, arg0_t, arg1_t, arg2_t)
#define PyAutoFunc_Register_Void_Args3(func, ret_t, arg0_t, arg1_t, arg2_t) PyAutoFunc_Register_Void_Args3_Macro(func, ret_t, arg0_t, arg1_t, arg2_t)
#define PyAutoFunc_Register_Args4(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t) PyAutoFunc_Register_Args4_Macro(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t)
#define PyAutoFunc_Register_Void_Args4(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t) PyAutoFunc_Register_Void_Args4_Macro(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t)
#define PyAutoFunc_Register_Args5(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t) PyAutoFunc_Register_Args5_Macro(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t)
#define PyAutoFunc_Register_Void_Args5(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t) PyAutoFunc_Register_Void_Args5_Macro(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t)

typedef void (*PyAutoCFunc)(void*,void*);

void PyAutoFunc_Register_TypeId(PyAutoCFunc ac_func, void* func, char* name, PyAutoType ret_tid, int num_args, ...);

#endif