#ifndef PyAutoFunctionMacros_h
#define PyAutoFunctionMacros_h

#define PyAutoFunction_RegisterArgs0_Macro(func, ret_t) \
void __PyAutoC_##func(void* out, void* args) { \
  *(ret_t*)out = func(); }; \
PyAutoFunction_Register_TypeId(__PyAutoC_##func, #func, PyTypeId(ret_t), 0)

#define PyAutoFunction_RegisterArgs0Void_Macro(func, ret_t) \
void __PyAutoC_##func(void* out, void* args) { \
  func(); }; \
PyAutoFunction_Register_TypeId(__PyAutoC_##func, #func, PyTypeId(ret_t), 0)

#define PyAutoFunction_RegisterArgs1_Macro(func, ret_t, arg0_t) \
void __PyAutoC_##func(void* out, void* args) { \
  arg0_t a0 = *(arg0_t*)args; \
  *(ret_t*)out = func(a0); }; \
PyAutoFunction_Register_TypeId(__PyAutoC_##func, #func, PyTypeId(ret_t), 1, PyTypeId(arg0_t))

#define PyAutoFunction_RegisterArgs1Void_Macro(func, ret_t, arg0_t) \
void __PyAutoC_##func(void* out, void* args) { \
  arg0_t a0 = *(arg0_t*)args; \
  func(a0); }; \
PyAutoFunction_Register_TypeId(__PyAutoC_##func, #func, PyTypeId(ret_t), 1, PyTypeId(arg0_t))

#define PyAutoFunction_RegisterArgs2_Macro(func, ret_t, arg0_t, arg1_t) \
void __PyAutoC_##func(void* out, void* args) { \
  arg0_t a0 = *(arg0_t*)args; \
  arg1_t a1 = *(arg1_t*)(args+sizeof(arg0_t)); \
  *(ret_t*)out = func(a0, a1); }; \
PyAutoFunction_Register_TypeId(__PyAutoC_##func, #func, PyTypeId(ret_t), 2, PyTypeId(arg0_t), PyTypeId(arg1_t))

#define PyAutoFunction_RegisterArgs2Void_Macro(func, ret_t, arg0_t, arg1_t) \
void __PyAutoC_##func(void* out, void* args) { \
  arg0_t a0 = *(arg0_t*)args; \
  arg1_t a1 = *(arg1_t*)(args+sizeof(arg0_t)); \
  func(a0, a1); }; \
PyAutoFunction_Register_TypeId(__PyAutoC_##func, #func, PyTypeId(ret_t), 2, PyTypeId(arg0_t), PyTypeId(arg1_t))

#define PyAutoFunction_RegisterArgs3_Macro(func, ret_t, arg0_t, arg1_t, arg2_t) \
void __PyAutoC_##func(void* out, void* args) { \
  arg0_t a0 = *(arg0_t*)args; \
  arg1_t a1 = *(arg1_t*)(args+sizeof(arg0_t)); \
  arg2_t a2 = *(arg2_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)); \
  *(ret_t*)out = func(a0, a1, a2); }; \
PyAutoFunction_Register_TypeId(__PyAutoC_##func, #func, PyTypeId(ret_t), 3, PyTypeId(arg0_t), PyTypeId(arg1_t), PyTypeId(arg2_t))

#define PyAutoFunction_RegisterArgs3Void_Macro(func, ret_t, arg0_t, arg1_t) \
void __PyAutoC_##func(void* out, void* args) { \
  arg0_t a0 = *(arg0_t*)args; \
  arg1_t a1 = *(arg1_t*)(args+sizeof(arg0_t)); \
  arg2_t a2 = *(arg2_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)); \
  func(a0, a1, a2); }; \
PyAutoFunction_Register_TypeId(__PyAutoC_##func, #func, PyTypeId(ret_t), 3, PyTypeId(arg0_t), PyTypeId(arg1_t), PyTypeId(arg2_t))

#define PyAutoFunction_RegisterArgs4_Macro(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t) \
void __PyAutoC_##func(void* out, void* args) { \
  arg0_t a0 = *(arg0_t*)args; \
  arg1_t a1 = *(arg1_t*)(args+sizeof(arg0_t)); \
  arg2_t a2 = *(arg2_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)); \
  arg3_t a3 = *(arg3_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)); \
  *(ret_t*)out = func(a0, a1, a2, a3); }; \
PyAutoFunction_Register_TypeId(__PyAutoC_##func, #func, PyTypeId(ret_t), 4, PyTypeId(arg0_t), PyTypeId(arg1_t), PyTypeId(arg2_t), PyTypeId(arg3_t))

#define PyAutoFunction_RegisterArgs4Void_Macro(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t) \
void __PyAutoC_##func(void* out, void* args) { \
  arg0_t a0 = *(arg0_t*)args; \
  arg1_t a1 = *(arg1_t*)(args+sizeof(arg0_t)); \
  arg2_t a2 = *(arg2_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)); \
  arg3_t a3 = *(arg3_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)); \
  func(a0, a1, a2, a3); }; \
PyAutoFunction_Register_TypeId(__PyAutoC_##func, #func, PyTypeId(ret_t), 4, PyTypeId(arg0_t), PyTypeId(arg1_t), PyTypeId(arg2_t), PyTypeId(arg3_t))

#define PyAutoFunction_RegisterArgs5_Macro(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t) \
void __PyAutoC_##func(void* out, void* args) { \
  arg0_t a0 = *(arg0_t*)args; \
  arg1_t a1 = *(arg1_t*)(args+sizeof(arg0_t)); \
  arg2_t a2 = *(arg2_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)); \
  arg3_t a3 = *(arg3_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)); \
  arg4_t a4 = *(arg4_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)+sizeof(arg3_t)); \
  *(ret_t*)out = func(a0, a1, a2, a3, a4); }; \
PyAutoFunction_Register_TypeId(__PyAutoC_##func, #func, PyTypeId(ret_t), 5, PyTypeId(arg0_t), PyTypeId(arg1_t), PyTypeId(arg2_t), PyTypeId(arg3_t), PyTypeId(arg4_t))

#define PyAutoFunction_RegisterArgs5Void_Macro(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t) \
void __PyAutoC_##func(void* out, void* args) { \
  arg0_t a0 = *(arg0_t*)args; \
  arg1_t a1 = *(arg1_t*)(args+sizeof(arg0_t)); \
  arg2_t a2 = *(arg2_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)); \
  arg3_t a3 = *(arg3_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)); \
  arg4_t a4 = *(arg4_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)+sizeof(arg3_t)); \
  func(a0, a1, a2, a3, a4); }; \
PyAutoFunction_Register_TypeId(__PyAutoC_##func, #func, PyTypeId(ret_t), 5, PyTypeId(arg0_t), PyTypeId(arg1_t), PyTypeId(arg2_t), PyTypeId(arg3_t), PyTypeId(arg4_t))

#define PyAutoFunction_RegisterArgs6_Macro(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t) \
void __PyAutoC_##func(void* out, void* args) { \
  arg0_t a0 = *(arg0_t*)args; \
  arg1_t a1 = *(arg1_t*)(args+sizeof(arg0_t)); \
  arg2_t a2 = *(arg2_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)); \
  arg3_t a3 = *(arg3_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)); \
  arg4_t a4 = *(arg4_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)+sizeof(arg3_t)); \
  arg5_t a5 = *(arg5_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)+sizeof(arg3_t)+sizeof(arg4_t)); \
  *(ret_t*)out = func(a0, a1, a2, a3, a4, a5); }; \
PyAutoFunction_Register_TypeId(__PyAutoC_##func, #func, PyTypeId(ret_t), 6, PyTypeId(arg0_t), PyTypeId(arg1_t), PyTypeId(arg2_t), PyTypeId(arg3_t), PyTypeId(arg4_t), PyTypeId(arg5_t))

#define PyAutoFunction_RegisterArgs6Void_Macro(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t) \
void __PyAutoC_##func(void* out, void* args) { \
  arg0_t a0 = *(arg0_t*)args; \
  arg1_t a1 = *(arg1_t*)(args+sizeof(arg0_t)); \
  arg2_t a2 = *(arg2_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)); \
  arg3_t a3 = *(arg3_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)); \
  arg4_t a4 = *(arg4_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)+sizeof(arg3_t)); \
  arg5_t a5 = *(arg5_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)+sizeof(arg3_t)+sizeof(arg4_t)); \
  func(a0, a1, a2, a3, a4, a5); }; \
PyAutoFunction_Register_TypeId(__PyAutoC_##func, #func, PyTypeId(ret_t), 6, PyTypeId(arg0_t), PyTypeId(arg1_t), PyTypeId(arg2_t), PyTypeId(arg3_t), PyTypeId(arg4_t), PyTypeId(arg5_t))

#define PyAutoFunction_RegisterArgs7_Macro(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t) \
void __PyAutoC_##func(void* out, void* args) { \
  arg0_t a0 = *(arg0_t*)args; \
  arg1_t a1 = *(arg1_t*)(args+sizeof(arg0_t)); \
  arg2_t a2 = *(arg2_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)); \
  arg3_t a3 = *(arg3_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)); \
  arg4_t a4 = *(arg4_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)+sizeof(arg3_t)); \
  arg5_t a5 = *(arg5_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)+sizeof(arg3_t)+sizeof(arg4_t)); \
  arg6_t a6 = *(arg6_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)+sizeof(arg3_t)+sizeof(arg4_t)+sizeof(arg5_t)); \
  *(ret_t*)out = func(a0, a1, a2, a3, a4, a5, a6); }; \
PyAutoFunction_Register_TypeId(__PyAutoC_##func, #func, PyTypeId(ret_t), 7, PyTypeId(arg0_t), PyTypeId(arg1_t), PyTypeId(arg2_t), PyTypeId(arg3_t), PyTypeId(arg4_t), PyTypeId(arg5_t), PyTypeId(arg6_t))

#define PyAutoFunction_RegisterArgs7Void_Macro(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t) \
void __PyAutoC_##func(void* out, void* args) { \
  arg0_t a0 = *(arg0_t*)args; \
  arg1_t a1 = *(arg1_t*)(args+sizeof(arg0_t)); \
  arg2_t a2 = *(arg2_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)); \
  arg3_t a3 = *(arg3_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)); \
  arg4_t a4 = *(arg4_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)+sizeof(arg3_t)); \
  arg5_t a5 = *(arg5_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)+sizeof(arg3_t)+sizeof(arg4_t)); \
  arg6_t a6 = *(arg6_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)+sizeof(arg3_t)+sizeof(arg4_t)+sizeof(arg5_t)); \
  func(a0, a1, a2, a3, a4, a5, a6); }; \
PyAutoFunction_Register_TypeId(__PyAutoC_##func, #func, PyTypeId(ret_t), 7, PyTypeId(arg0_t), PyTypeId(arg1_t), PyTypeId(arg2_t), PyTypeId(arg3_t), PyTypeId(arg4_t), PyTypeId(arg5_t), PyTypeId(arg6_t))

#define PyAutoFunction_RegisterArgs8_Macro(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t) \
void __PyAutoC_##func(void* out, void* args) { \
  arg0_t a0 = *(arg0_t*)args; \
  arg1_t a1 = *(arg1_t*)(args+sizeof(arg0_t)); \
  arg2_t a2 = *(arg2_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)); \
  arg3_t a3 = *(arg3_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)); \
  arg4_t a4 = *(arg4_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)+sizeof(arg3_t)); \
  arg5_t a5 = *(arg5_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)+sizeof(arg3_t)+sizeof(arg4_t)); \
  arg6_t a6 = *(arg6_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)+sizeof(arg3_t)+sizeof(arg4_t)+sizeof(arg5_t)); \
  arg7_t a7 = *(arg7_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)+sizeof(arg3_t)+sizeof(arg4_t)+sizeof(arg5_t)+sizeof(arg6_t)); \
  *(ret_t*)out = func(a0, a1, a2, a3, a4, a5, a6, a7); }; \
PyAutoFunction_Register_TypeId(__PyAutoC_##func, #func, PyTypeId(ret_t), 8, PyTypeId(arg0_t), PyTypeId(arg1_t), PyTypeId(arg2_t), PyTypeId(arg3_t), PyTypeId(arg4_t), PyTypeId(arg5_t), PyTypeId(arg6_t), PyTypeId(arg7_t))

#define PyAutoFunction_RegisterArgs8Void_Macro(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t) \
void __PyAutoC_##func(void* out, void* args) { \
  arg0_t a0 = *(arg0_t*)args; \
  arg1_t a1 = *(arg1_t*)(args+sizeof(arg0_t)); \
  arg2_t a2 = *(arg2_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)); \
  arg3_t a3 = *(arg3_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)); \
  arg4_t a4 = *(arg4_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)+sizeof(arg3_t)); \
  arg5_t a5 = *(arg5_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)+sizeof(arg3_t)+sizeof(arg4_t)); \
  arg6_t a6 = *(arg6_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)+sizeof(arg3_t)+sizeof(arg4_t)+sizeof(arg5_t)); \
  arg7_t a7 = *(arg7_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)+sizeof(arg3_t)+sizeof(arg4_t)+sizeof(arg5_t)+sizeof(arg6_t)); \
  func(a0, a1, a2, a3, a4, a5, a6, a7); }; \
PyAutoFunction_Register_TypeId(__PyAutoC_##func, #func, PyTypeId(ret_t), 8, PyTypeId(arg0_t), PyTypeId(arg1_t), PyTypeId(arg2_t), PyTypeId(arg3_t), PyTypeId(arg4_t), PyTypeId(arg5_t), PyTypeId(arg6_t), PyTypeId(arg7_t))

#define PyAutoFunction_RegisterArgs9_Macro(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t, arg8_t) \
void __PyAutoC_##func(void* out, void* args) { \
  arg0_t a0 = *(arg0_t*)args; \
  arg1_t a1 = *(arg1_t*)(args+sizeof(arg0_t)); \
  arg2_t a2 = *(arg2_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)); \
  arg3_t a3 = *(arg3_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)); \
  arg4_t a4 = *(arg4_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)+sizeof(arg3_t)); \
  arg5_t a5 = *(arg5_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)+sizeof(arg3_t)+sizeof(arg4_t)); \
  arg6_t a6 = *(arg6_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)+sizeof(arg3_t)+sizeof(arg4_t)+sizeof(arg5_t)); \
  arg7_t a7 = *(arg7_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)+sizeof(arg3_t)+sizeof(arg4_t)+sizeof(arg5_t)+sizeof(arg6_t)); \
  arg8_t a8 = *(arg8_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)+sizeof(arg3_t)+sizeof(arg4_t)+sizeof(arg5_t)+sizeof(arg6_t)+sizeof(arg7_t)); \
  *(ret_t*)out = func(a0, a1, a2, a3, a4, a5, a6, a7, a8); }; \
PyAutoFunction_Register_TypeId(__PyAutoC_##func, #func, PyTypeId(ret_t), 9, PyTypeId(arg0_t), PyTypeId(arg1_t), PyTypeId(arg2_t), PyTypeId(arg3_t), PyTypeId(arg4_t), PyTypeId(arg5_t), PyTypeId(arg6_t), PyTypeId(arg7_t), PyTypeId(arg8_t))

#define PyAutoFunction_RegisterArgs9Void_Macro(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t, arg8_t) \
void __PyAutoC_##func(void* out, void* args) { \
  arg0_t a0 = *(arg0_t*)args; \
  arg1_t a1 = *(arg1_t*)(args+sizeof(arg0_t)); \
  arg2_t a2 = *(arg2_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)); \
  arg3_t a3 = *(arg3_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)); \
  arg4_t a4 = *(arg4_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)+sizeof(arg3_t)); \
  arg5_t a5 = *(arg5_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)+sizeof(arg3_t)+sizeof(arg4_t)); \
  arg6_t a6 = *(arg6_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)+sizeof(arg3_t)+sizeof(arg4_t)+sizeof(arg5_t)); \
  arg7_t a7 = *(arg7_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)+sizeof(arg3_t)+sizeof(arg4_t)+sizeof(arg5_t)+sizeof(arg6_t)); \
  arg8_t a8 = *(arg8_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)+sizeof(arg3_t)+sizeof(arg4_t)+sizeof(arg5_t)+sizeof(arg6_t)+sizeof(arg7_t)); \
  func(a0, a1, a2, a3, a4, a5, a6, a7, a8); }; \
PyAutoFunction_Register_TypeId(__PyAutoC_##func, #func, PyTypeId(ret_t), 9, PyTypeId(arg0_t), PyTypeId(arg1_t), PyTypeId(arg2_t), PyTypeId(arg3_t), PyTypeId(arg4_t), PyTypeId(arg5_t), PyTypeId(arg6_t), PyTypeId(arg7_t), PyTypeId(arg8_t))

#define PyAutoFunction_RegisterArgs10_Macro(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t, arg8_t, arg9_t) \
void __PyAutoC_##func(void* out, void* args) { \
  arg0_t a0 = *(arg0_t*)args; \
  arg1_t a1 = *(arg1_t*)(args+sizeof(arg0_t)); \
  arg2_t a2 = *(arg2_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)); \
  arg3_t a3 = *(arg3_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)); \
  arg4_t a4 = *(arg4_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)+sizeof(arg3_t)); \
  arg5_t a5 = *(arg5_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)+sizeof(arg3_t)+sizeof(arg4_t)); \
  arg6_t a6 = *(arg6_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)+sizeof(arg3_t)+sizeof(arg4_t)+sizeof(arg5_t)); \
  arg7_t a7 = *(arg7_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)+sizeof(arg3_t)+sizeof(arg4_t)+sizeof(arg5_t)+sizeof(arg6_t)); \
  arg8_t a8 = *(arg8_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)+sizeof(arg3_t)+sizeof(arg4_t)+sizeof(arg5_t)+sizeof(arg6_t)+sizeof(arg7_t)); \
  arg9_t a9 = *(arg9_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)+sizeof(arg3_t)+sizeof(arg4_t)+sizeof(arg5_t)+sizeof(arg6_t)+sizeof(arg7_t)+sizeof(arg8_t)); \
  *(ret_t*)out = func(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9); }; \
PyAutoFunction_Register_TypeId(__PyAutoC_##func, #func, PyTypeId(ret_t), 10, PyTypeId(arg0_t), PyTypeId(arg1_t), PyTypeId(arg2_t), PyTypeId(arg3_t), PyTypeId(arg4_t), PyTypeId(arg5_t), PyTypeId(arg6_t), PyTypeId(arg7_t), PyTypeId(arg8_t), PyTypeId(arg9_t))

#define PyAutoFunction_RegisterArgs10Void_Macro(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t, arg8_t, arg9_t) \
void __PyAutoC_##func(void* out, void* args) { \
  arg0_t a0 = *(arg0_t*)args; \
  arg1_t a1 = *(arg1_t*)(args+sizeof(arg0_t)); \
  arg2_t a2 = *(arg2_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)); \
  arg3_t a3 = *(arg3_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)); \
  arg4_t a4 = *(arg4_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)+sizeof(arg3_t)); \
  arg5_t a5 = *(arg5_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)+sizeof(arg3_t)+sizeof(arg4_t)); \
  arg6_t a6 = *(arg6_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)+sizeof(arg3_t)+sizeof(arg4_t)+sizeof(arg5_t)); \
  arg7_t a7 = *(arg7_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)+sizeof(arg3_t)+sizeof(arg4_t)+sizeof(arg5_t)+sizeof(arg6_t)); \
  arg8_t a8 = *(arg8_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)+sizeof(arg3_t)+sizeof(arg4_t)+sizeof(arg5_t)+sizeof(arg6_t)+sizeof(arg7_t)); \
  arg9_t a9 = *(arg9_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)+sizeof(arg3_t)+sizeof(arg4_t)+sizeof(arg5_t)+sizeof(arg6_t)+sizeof(arg7_t)+sizeof(arg8_t)); \
  func(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9); }; \
PyAutoFunction_Register_TypeId(__PyAutoC_##func, #func, PyTypeId(ret_t), 10, PyTypeId(arg0_t), PyTypeId(arg1_t), PyTypeId(arg2_t), PyTypeId(arg3_t), PyTypeId(arg4_t), PyTypeId(arg5_t), PyTypeId(arg6_t), PyTypeId(arg7_t), PyTypeId(arg8_t), PyTypeId(arg9_t))

#endif
