#ifndef PyAutoFunction_h
#define PyAutoFunction_h

#include "Python.h"
#include "PyAutoType.h"
#include "PyAutoFunctionMacros.h"

void PyAutoFunction_Initialize(void);
void PyAutoFunction_Finalize(void);

PyObject* PyAutoFunction_Call(void* c_func, PyObject* args);
PyObject* PyAutoFunction_CallByName(char* c_func_name, PyObject* args);

#define PyAutoFunction_RegisterArgs0(func, ret_t) PyAutoFunction_RegisterArgs0_Macro(func, ret_t)
#define PyAutoFunction_RegisterArgs0Void(func, ret_t) PyAutoFunction_RegisterArgs0Void_Macro(func, ret_t)
#define PyAutoFunction_RegisterArgs1(func, ret_t, arg0_t) PyAutoFunction_RegisterArgs1_Macro(func, ret_t, arg0_t) 
#define PyAutoFunction_RegisterArgs1Void(func, ret_t, arg0_t) PyAutoFunction_RegisterArgs1Void_Macro(func, ret_t, arg0_t)
#define PyAutoFunction_RegisterArgs2(func, ret_t, arg0_t, arg1_t) PyAutoFunction_RegisterArgs2_Macro(func, ret_t, arg0_t, arg1_t)
#define PyAutoFunction_RegisterArgs2Void(func, ret_t, arg0_t, arg1_t) PyAutoFunction_RegisterArgs2Void_Macro(func, ret_t, arg0_t, arg1_t)
#define PyAutoFunction_RegisterArgs3(func, ret_t, arg0_t, arg1_t, arg2_t) PyAutoFunction_RegisterArgs3_Macro(func, ret_t, arg0_t, arg1_t, arg2_t)
#define PyAutoFunction_RegisterArgs3Void(func, ret_t, arg0_t, arg1_t, arg2_t) PyAutoFunction_RegisterArgs3Void_Macro(func, ret_t, arg0_t, arg1_t, arg2_t)
#define PyAutoFunction_RegisterArgs4(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t) PyAutoFunction_RegisterArgs4_Macro(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t)
#define PyAutoFunction_RegisterArgs4Void(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t) PyAutoFunction_RegisterArgs4Void_Macro(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t)
#define PyAutoFunction_RegisterArgs5(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t) PyAutoFunction_RegisterArgs5_Macro(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t)
#define PyAutoFunction_RegisterArgs5Void(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t) PyAutoFunction_RegisterArgs5Void_Macro(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t)
#define PyAutoFunction_RegisterArgs6(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t) PyAutoFunction_RegisterArgs6_Macro(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t)
#define PyAutoFunction_RegisterArgs6Void(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t) PyAutoFunction_RegisterArgs6Void_Macro(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t)
#define PyAutoFunction_RegisterArgs7(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t) PyAutoFunction_RegisterArgs7_Macro(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t)
#define PyAutoFunction_RegisterArgs7Void(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t) PyAutoFunction_RegisterArgs7Void_Macro(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t)
#define PyAutoFunction_RegisterArgs8(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t) PyAutoFunction_RegisterArgs8_Macro(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t)
#define PyAutoFunction_RegisterVoidArgs8(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t) PyAutoFunction_RegisterArgs8Void_Macro(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t)
#define PyAutoFunction_RegisterArgs9(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t, arg8_t) PyAutoFunction_RegisterArgs9_Macro(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t, arg8_t)
#define PyAutoFunction_RegisterVoidArgs9(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t, arg8_t) PyAutoFunction_RegisterArgs9Void_Macro(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t, arg8_t)
#define PyAutoFunction_RegisterArgs10(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t, arg8_t, arg9_t) PyAutoFunction_RegisterArgs10_Macro(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t, arg8_t, arg9_t)
#define PyAutoFunction_RegisterVoidArgs10(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t, arg8_t, arg9_t) PyAutoFunction_RegisterArgs10Void_Macro(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t, arg8_t, arg9_t)

typedef void (*PyAutoCFunc)(void*,void*);

void PyAutoFunction_Register_TypeId(PyAutoCFunc ac_func, void* func, char* name, PyAutoType ret_tid, int num_args, ...);

#endif
