#ifndef PyAutoFunctionMacros_h
#define PyAutoFunctionMacros_h

#define PyAutoFunc_Register_Args0_Macro(func, ret_t) \
void __PyAutoC_##func(void* out, void* args) { \
  *(ret_t*)out = func(); }; \
PyAutoFunc_Register_TypeId(__PyAutoC_##func, func, #func, PyTypeId(ret_t), 0)

#define PyAutoFunc_Register_Void_Args0_Macro(func, ret_t) \
void __PyAutoC_##func(void* out, void* args) { \
  func(); }; \
PyAutoFunc_Register_TypeId(__PyAutoC_##func, func, #func, PyTypeId(ret_t), 0)

#define PyAutoFunc_Register_Args1_Macro(func, ret_t, arg0_t) \
void __PyAutoC_##func(void* out, void* args) { \
  arg0_t a0 = *(arg0_t*)args; \
  *(ret_t*)out = func(a0); }; \
PyAutoFunc_Register_TypeId(__PyAutoC_##func, func, #func, PyTypeId(ret_t), 1, PyTypeId(arg0_t))

#define PyAutoFunc_Register_Void_Args1_Macro(func, ret_t, arg0_t) \
void __PyAutoC_##func(void* out, void* args) { \
  arg0_t a0 = *(arg0_t*)args; \
  func(a0); }; \
PyAutoFunc_Register_TypeId(__PyAutoC_##func, func, #func, PyTypeId(ret_t), 1, PyTypeId(arg0_t))

#define PyAutoFunc_Register_Args2_Macro(func, ret_t, arg0_t, arg1_t) \
void __PyAutoC_##func(void* out, void* args) { \
  arg0_t a0 = *(arg0_t*)args; \
  arg1_t a1 = *(arg1_t*)(args+sizeof(arg0_t)); \
  *(ret_t*)out = func(a0, a1); }; \
PyAutoFunc_Register_TypeId(__PyAutoC_##func, func, #func, PyTypeId(ret_t), 2, PyTypeId(arg0_t), PyTypeId(arg1_t))

#define PyAutoFunc_Register_Void_Args2_Macro(func, ret_t, arg0_t, arg1_t) \
void __PyAutoC_##func(void* out, void* args) { \
  arg0_t a0 = *(arg0_t*)args; \
  arg1_t a1 = *(arg1_t*)(args+sizeof(arg0_t)); \
  func(a0, a1); }; \
PyAutoFunc_Register_TypeId(__PyAutoC_##func, func, #func, PyTypeId(ret_t), 2, PyTypeId(arg0_t), PyTypeId(arg1_t))

#define PyAutoFunc_Register_Args3_Macro(func, ret_t, arg0_t, arg1_t, arg2_t) \
void __PyAutoC_##func(void* out, void* args) { \
  arg0_t a0 = *(arg0_t*)args; \
  arg1_t a1 = *(arg1_t*)(args+sizeof(arg0_t)); \
  arg2_t a2 = *(arg2_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)); \
  *(ret_t*)out = func(a0, a1, a2); }; \
PyAutoFunc_Register_TypeId(__PyAutoC_##func, func, #func, PyTypeId(ret_t), 3, PyTypeId(arg0_t), PyTypeId(arg1_t), PyTypeId(arg2_t))

#define PyAutoFunc_Register_Void_Args3_Macro(func, ret_t, arg0_t, arg1_t) \
void __PyAutoC_##func(void* out, void* args) { \
  arg0_t a0 = *(arg0_t*)args; \
  arg1_t a1 = *(arg1_t*)(args+sizeof(arg0_t)); \
  arg2_t a2 = *(arg2_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)); \
  func(a0, a1, a2); }; \
PyAutoFunc_Register_TypeId(__PyAutoC_##func, func, #func, PyTypeId(ret_t), 3, PyTypeId(arg0_t), PyTypeId(arg1_t), PyTypeId(arg2_t))

#define PyAutoFunc_Register_Args4_Macro(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t) \
void __PyAutoC_##func(void* out, void* args) { \
  arg0_t a0 = *(arg0_t*)args; \
  arg1_t a1 = *(arg1_t*)(args+sizeof(arg0_t)); \
  arg2_t a2 = *(arg2_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)); \
  arg3_t a3 = *(arg3_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)); \
  *(ret_t*)out = func(a0, a1, a2, a3); }; \
PyAutoFunc_Register_TypeId(__PyAutoC_##func, func, #func, PyTypeId(ret_t), 4, PyTypeId(arg0_t), PyTypeId(arg1_t), PyTypeId(arg2_t), PyTypeId(arg3_t))

#define PyAutoFunc_Register_Void_Args4_Macro(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t) \
void __PyAutoC_##func(void* out, void* args) { \
  arg0_t a0 = *(arg0_t*)args; \
  arg1_t a1 = *(arg1_t*)(args+sizeof(arg0_t)); \
  arg2_t a2 = *(arg2_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)); \
  arg3_t a3 = *(arg3_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)); \
  func(a0, a1, a2, a3); }; \
PyAutoFunc_Register_TypeId(__PyAutoC_##func, func, #func, PyTypeId(ret_t), 4, PyTypeId(arg0_t), PyTypeId(arg1_t), PyTypeId(arg2_t), PyTypeId(arg3_t))

#define PyAutoFunc_Register_Args5_Macro(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t) \
void __PyAutoC_##func(void* out, void* args) { \
  arg0_t a0 = *(arg0_t*)args; \
  arg1_t a1 = *(arg1_t*)(args+sizeof(arg0_t)); \
  arg2_t a2 = *(arg2_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)); \
  arg3_t a3 = *(arg3_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)); \
  arg4_t a4 = *(arg4_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)+sizeof(arg3_t)); \
  *(ret_t*)out = func(a0, a1, a2, a3, a4); }; \
PyAutoFunc_Register_TypeId(__PyAutoC_##func, func, #func, PyTypeId(ret_t), 5, PyTypeId(arg0_t), PyTypeId(arg1_t), PyTypeId(arg2_t), PyTypeId(arg3_t), PyTypeId(arg4_t))

#define PyAutoFunc_Register_Void_Args5_Macro(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t) \
void __PyAutoC_##func(void* out, void* args) { \
  arg0_t a0 = *(arg0_t*)args; \
  arg1_t a1 = *(arg1_t*)(args+sizeof(arg0_t)); \
  arg2_t a2 = *(arg2_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)); \
  arg3_t a3 = *(arg3_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)); \
  arg4_t a4 = *(arg4_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)+sizeof(arg3_t)); \
  func(a0, a1, a2, a3, a4); }; \
PyAutoFunc_Register_TypeId(__PyAutoC_##func, func, #func, PyTypeId(ret_t), 5, PyTypeId(arg0_t), PyTypeId(arg1_t), PyTypeId(arg2_t), PyTypeId(arg3_t), PyTypeId(arg4_t))

#endif