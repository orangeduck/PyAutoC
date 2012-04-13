#include "PyAutoC.h"

void PyAutoC_Initialize(void) {
  
  PyAutoType_Initialize();
  PyAutoConvert_Initialize();
  PyAutoFunction_Initialize();
  PyAutoStruct_Initialize();
  
}

void PyAutoC_Finalize(void) {
  
  PyAutoStruct_Finalize();
  PyAutoFunction_Finalize();
  PyAutoConvert_Finalize();
  PyAutoType_Finalize();
  
}
