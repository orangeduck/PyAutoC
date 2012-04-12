#ifndef PyAutoFunctionMacros_h
#define PyAutoFunctionMacros_h

#define PyAutoFunction_RegisterArgs0_Macro(func, ret_t) \
void __PyAutoC_##func(void* out, void* args) { \
  *(ret_t*)out = func(); }; \
PyAutoFunction_Register_TypeId(__PyAutoC_##func, func, #func, PyTypeId(ret_t), 0)

#define PyAutoFunction_RegisterVoidArgs0_Macro(func, ret_t) \
void __PyAutoC_##func(void* out, void* args) { \
  func(); }; \
PyAutoFunction_Register_TypeId(__PyAutoC_##func, func, #func, PyTypeId(ret_t), 0)

#define PyAutoFunction_RegisterArgs1_Macro(func, ret_t, arg0_t) \
void __PyAutoC_##func(void* out, void* args) { \
  arg0_t a0 = *(arg0_t*)args; \
  *(ret_t*)out = func(a0); }; \
PyAutoFunction_Register_TypeId(__PyAutoC_##func, func, #func, PyTypeId(ret_t), 1, PyTypeId(arg0_t))

#define PyAutoFunction_RegisterVoidArgs1_Macro(func, ret_t, arg0_t) \
void __PyAutoC_##func(void* out, void* args) { \
  arg0_t a0 = *(arg0_t*)args; \
  func(a0); }; \
PyAutoFunction_Register_TypeId(__PyAutoC_##func, func, #func, PyTypeId(ret_t), 1, PyTypeId(arg0_t))

#define PyAutoFunction_RegisterArgs2_Macro(func, ret_t, arg0_t, arg1_t) \
void __PyAutoC_##func(void* out, void* args) { \
  arg0_t a0 = *(arg0_t*)args; \
  arg1_t a1 = *(arg1_t*)(args+sizeof(arg0_t)); \
  *(ret_t*)out = func(a0, a1); }; \
PyAutoFunction_Register_TypeId(__PyAutoC_##func, func, #func, PyTypeId(ret_t), 2, PyTypeId(arg0_t), PyTypeId(arg1_t))

#define PyAutoFunction_RegisterVoidArgs2_Macro(func, ret_t, arg0_t, arg1_t) \
void __PyAutoC_##func(void* out, void* args) { \
  arg0_t a0 = *(arg0_t*)args; \
  arg1_t a1 = *(arg1_t*)(args+sizeof(arg0_t)); \
  func(a0, a1); }; \
PyAutoFunction_Register_TypeId(__PyAutoC_##func, func, #func, PyTypeId(ret_t), 2, PyTypeId(arg0_t), PyTypeId(arg1_t))

#define PyAutoFunction_RegisterArgs3_Macro(func, ret_t, arg0_t, arg1_t, arg2_t) \
void __PyAutoC_##func(void* out, void* args) { \
  arg0_t a0 = *(arg0_t*)args; \
  arg1_t a1 = *(arg1_t*)(args+sizeof(arg0_t)); \
  arg2_t a2 = *(arg2_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)); \
  *(ret_t*)out = func(a0, a1, a2); }; \
PyAutoFunction_Register_TypeId(__PyAutoC_##func, func, #func, PyTypeId(ret_t), 3, PyTypeId(arg0_t), PyTypeId(arg1_t), PyTypeId(arg2_t))

#define PyAutoFunction_RegisterVoidArgs3_Macro(func, ret_t, arg0_t, arg1_t) \
void __PyAutoC_##func(void* out, void* args) { \
  arg0_t a0 = *(arg0_t*)args; \
  arg1_t a1 = *(arg1_t*)(args+sizeof(arg0_t)); \
  arg2_t a2 = *(arg2_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)); \
  func(a0, a1, a2); }; \
PyAutoFunction_Register_TypeId(__PyAutoC_##func, func, #func, PyTypeId(ret_t), 3, PyTypeId(arg0_t), PyTypeId(arg1_t), PyTypeId(arg2_t))

#define PyAutoFunction_RegisterArgs4_Macro(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t) \
void __PyAutoC_##func(void* out, void* args) { \
  arg0_t a0 = *(arg0_t*)args; \
  arg1_t a1 = *(arg1_t*)(args+sizeof(arg0_t)); \
  arg2_t a2 = *(arg2_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)); \
  arg3_t a3 = *(arg3_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)); \
  *(ret_t*)out = func(a0, a1, a2, a3); }; \
PyAutoFunction_Register_TypeId(__PyAutoC_##func, func, #func, PyTypeId(ret_t), 4, PyTypeId(arg0_t), PyTypeId(arg1_t), PyTypeId(arg2_t), PyTypeId(arg3_t))

#define PyAutoFunction_RegisterVoidArgs4_Macro(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t) \
void __PyAutoC_##func(void* out, void* args) { \
  arg0_t a0 = *(arg0_t*)args; \
  arg1_t a1 = *(arg1_t*)(args+sizeof(arg0_t)); \
  arg2_t a2 = *(arg2_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)); \
  arg3_t a3 = *(arg3_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)); \
  func(a0, a1, a2, a3); }; \
PyAutoFunction_Register_TypeId(__PyAutoC_##func, func, #func, PyTypeId(ret_t), 4, PyTypeId(arg0_t), PyTypeId(arg1_t), PyTypeId(arg2_t), PyTypeId(arg3_t))

#define PyAutoFunction_RegisterArgs5_Macro(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t) \
void __PyAutoC_##func(void* out, void* args) { \
  arg0_t a0 = *(arg0_t*)args; \
  arg1_t a1 = *(arg1_t*)(args+sizeof(arg0_t)); \
  arg2_t a2 = *(arg2_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)); \
  arg3_t a3 = *(arg3_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)); \
  arg4_t a4 = *(arg4_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)+sizeof(arg3_t)); \
  *(ret_t*)out = func(a0, a1, a2, a3, a4); }; \
PyAutoFunction_Register_TypeId(__PyAutoC_##func, func, #func, PyTypeId(ret_t), 5, PyTypeId(arg0_t), PyTypeId(arg1_t), PyTypeId(arg2_t), PyTypeId(arg3_t), PyTypeId(arg4_t))

#define PyAutoFunction_RegisterVoidArgs5_Macro(func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t) \
void __PyAutoC_##func(void* out, void* args) { \
  arg0_t a0 = *(arg0_t*)args; \
  arg1_t a1 = *(arg1_t*)(args+sizeof(arg0_t)); \
  arg2_t a2 = *(arg2_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)); \
  arg3_t a3 = *(arg3_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)); \
  arg4_t a4 = *(arg4_t*)(args+sizeof(arg0_t)+sizeof(arg1_t)+sizeof(arg2_t)+sizeof(arg3_t)); \
  func(a0, a1, a2, a3, a4); }; \
PyAutoFunction_Register_TypeId(__PyAutoC_##func, func, #func, PyTypeId(ret_t), 5, PyTypeId(arg0_t), PyTypeId(arg1_t), PyTypeId(arg2_t), PyTypeId(arg3_t), PyTypeId(arg4_t))

#endif