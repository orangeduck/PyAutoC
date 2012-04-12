#include "PyAutoC.h"

void PyAutoC_Initialize() {
  
  PyAutoType_Initialize();
  PyAutoConvert_Initialize();
  PyAutoFunction_Initialize();
  PyAutoStruct_Initialize();
  
}

void PyAutoC_Finalize() {
  
  PyAutoStruct_Finalize();
  PyAutoFunction_Finalize();
  PyAutoConvert_Finalize();
  PyAutoType_Finalize();
  
}