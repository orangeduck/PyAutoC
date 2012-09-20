#include "PyAutoC.h"

typedef struct {
  PyAutoType type;
  int offset;
  char* name;
} struct_member_entry;

typedef struct {
  PyAutoType type_id;
  int num_members;
  int num_reserved_members;
  struct_member_entry** members;
} struct_entry;

static PyAutoHashtable* struct_table;

void PyAutoStruct_Initialize() {
  struct_table = PyAutoHashtable_New(256);
}

static void struct_entry_delete(struct_entry* se) {

  for(int i = 0; i < se->num_members; i++) {
    free(se->members[i]->name);
    free(se->members[i]);
  }
  
  free(se->members);
  free(se);
  
}

void PyAutoStruct_Finalize() {
  
  PyAutoHashtable_Map(struct_table, (void(*)(void*))struct_entry_delete);
  PyAutoHashtable_Delete(struct_table);
  
}

PyObject* PyAutoStruct_Get_TypeId(PyAutoType type, const void* cstruct, size_t offset) {
  
  struct_entry* se = PyAutoHashtable_Get(struct_table, PyAutoType_Name(type));
  if (se != NULL) {
  
    for(int j = 0; j < se->num_members; j++) {
    if (se->members[j]->offset == offset) {
      struct_member_entry* sme = se->members[j];
      return PyAutoConvert_From_TypeId(sme->type, cstruct+sme->offset);
    }
    }
    
    return PyErr_Format(PyExc_NameError, "PyAutoStruct: Member offset '%i' not registered for struct '%s'!", offset, PyAutoType_Name(type));
  }
  
  return PyErr_Format(PyExc_NameError, "PyAutoStruct: Struct '%s' not registered!", PyAutoType_Name(type));
}

bool PyAutoStruct_Has_TypeId(PyAutoType type, size_t offset) {
  
  struct_entry* se = PyAutoHashtable_Get(struct_table, PyAutoType_Name(type));
  if (se != NULL) {
    for(int j = 0; j < se->num_members; j++) {
      if (se->members[j]->offset == offset) { return true; }
    }
    return false;
  }
  
  PyErr_Format(PyExc_NameError, "PyAutoStruct: Struct '%s' not registered!", PyAutoType_Name(type));
  return false;
}

PyObject* PyAutoStruct_Set_TypeId(PyAutoType type, void* cstruct, size_t offset, PyObject* val) {

  struct_entry* se = PyAutoHashtable_Get(struct_table, PyAutoType_Name(type));
  if (se != NULL) {
    
    for(int j = 0; j < se->num_members; j++) {
    if (se->members[j]->offset == offset) {
      struct_member_entry* sme = se->members[j];
      PyAutoConvert_To_TypeId(sme->type, val, cstruct+sme->offset);
      if (PyErr_Occurred()) { return NULL; } else { Py_RETURN_NONE; }
    }
    }
    
    return PyErr_Format(PyExc_NameError, "PyAutoStruct: Member offset '%i' not registered for struct '%s'!", offset, PyAutoType_Name(type));
  }
  
  return PyErr_Format(PyExc_NameError, "PyAutoStruct: Struct '%s' not registered!", PyAutoType_Name(type));
}

PyObject* PyAutoStruct_GetMember_TypeId(PyAutoType type, const void* cstruct, const char* member) {
  
  struct_entry* se = PyAutoHashtable_Get(struct_table, PyAutoType_Name(type));
  if (se != NULL) {
  
    for(int j = 0; j < se->num_members; j++) {
    if (strcmp(se->members[j]->name, member) == 0) {
      struct_member_entry* sme = se->members[j];
      return PyAutoConvert_From_TypeId(sme->type, cstruct+sme->offset);
    }
    }
    
    return PyErr_Format(PyExc_NameError, "PyAutoStruct: Member '%s' not registered for struct '%s'!", member, PyAutoType_Name(type));
  }
  
  return PyErr_Format(PyExc_NameError, "PyAutoStruct: Struct '%s' not registered!", PyAutoType_Name(type));
}

bool PyAutoStruct_HasMember_TypeId(PyAutoType type, const char* member) {
  
  struct_entry* se = PyAutoHashtable_Get(struct_table, PyAutoType_Name(type));
  if (se != NULL) {
  
    for(int j = 0; j < se->num_members; j++) {
    if (strcmp(se->members[j]->name, member) == 0) {
      return true;
    }
    }
    
    return false;
  }
  
  PyErr_Format(PyExc_NameError, "PyAutoStruct: Struct '%s' not registered!", PyAutoType_Name(type));
  return false;
}

PyObject* PyAutoStruct_SetMember_TypeId(PyAutoType type, void* cstruct, const char* member, PyObject* val) {

  struct_entry* se = PyAutoHashtable_Get(struct_table, PyAutoType_Name(type));
  if (se != NULL) {
    
    for(int j = 0; j < se->num_members; j++) {
    if (strcmp(se->members[j]->name, member) == 0) {
      struct_member_entry* sme = se->members[j];
      PyAutoConvert_To_TypeId(sme->type, val, cstruct+sme->offset);
      if (PyErr_Occurred()) { return NULL; } else { Py_RETURN_NONE; }
    }
    }
    
    return PyErr_Format(PyExc_NameError, "PyAutoStruct: Member '%s' not registered for struct '%s'!", member, PyAutoType_Name(type));
  }
  
  return PyErr_Format(PyExc_NameError, "PyAutoStruct: Struct '%s' not registered!", PyAutoType_Name(type));
}

void PyAutoStruct_Register_TypeId(PyAutoType type) {
  
  struct_entry* se = malloc(sizeof(struct_entry));
  se->type_id = type;
  se->num_members = 0;
  se->num_reserved_members = 32;
  se->members = malloc(sizeof(struct_member_entry*) * se->num_reserved_members);
  
  PyAutoHashtable_Set(struct_table, PyAutoType_Name(type), se);
  
}


void PyAutoStruct_RegisterMember_TypeId(PyAutoType type, const char* member, PyAutoType member_type, size_t offset) {

  struct_entry* se = PyAutoHashtable_Get(struct_table, PyAutoType_Name(type));
  if (se != NULL) {
    
    if (se->num_members >= se->num_reserved_members) {
      se->num_reserved_members += 32;
      se->members = realloc(se->members, sizeof(struct_member_entry*) * se->num_reserved_members);
    }
    
    struct_member_entry* sme = malloc(sizeof(struct_member_entry));
    sme->type = member_type;
    sme->offset = offset;
    sme->name = malloc(strlen(member) + 1);
    strcpy(sme->name, member);
    
    se->members[se->num_members] = sme;
    se->num_members++;
    return;
    
  }
  
  PyErr_Format(PyExc_NameError, "PyAutoStruct: Struct '%s' not registered!", PyAutoType_Name(type));
  return;

}

bool PyAutoStruct_IsRegistered_TypeId(PyAutoType type) {
  
  struct_entry* se = PyAutoHashtable_Get(struct_table, PyAutoType_Name(type));
  return (se != NULL);
   
}

PyObject* PyAutoStruct_Convert_From_TypeId(PyAutoType type, const void* cstruct) {
  
  struct_entry* se = PyAutoHashtable_Get(struct_table, PyAutoType_Name(type));
  if (se != NULL) {
    
    PyObject* globals = PyDict_New();
    PyDict_SetItemString(globals, "__builtins__", PyEval_GetBuiltins());
    
    char fmtstring[1024];
    sprintf(fmtstring, "class PyAutoStruct_%s(object): pass\n", PyAutoType_Name(type)); 
    PyObject* ret = PyRun_String(fmtstring, Py_file_input, globals, globals);
    Py_DECREF(ret);
    
    sprintf(fmtstring, "PyAutoStruct_%s", PyAutoType_Name(type)); 
    PyObject* new_class = PyDict_GetItemString(globals, fmtstring);
    Py_DECREF(globals);
    
    PyObject* args = PyTuple_New(0);
    PyObject* instance = PyObject_Call(new_class, args, NULL);
    Py_DECREF(args);
    
    for(int j = 0; j < se->num_members; j++) {
      struct_member_entry* sme = se->members[j];
      PyObject* member = PyAutoConvert_From_TypeId(sme->type, cstruct+sme->offset);
      if (member == NULL) { return NULL; }
      PyObject_SetAttrString(instance, sme->name, member);
      Py_DECREF(member);
    }
    
    return instance;
  }
  
  return PyErr_Format(PyExc_NameError, "PyAutoStruct: Struct '%s' not registered!", PyAutoType_Name(type));

}

void PyAutoStruct_Convert_To_TypeId(PyAutoType type, PyObject* pyobj, void* out) {

  struct_entry* se = PyAutoHashtable_Get(struct_table, PyAutoType_Name(type));
  if (se != NULL) {
    
    for(int j = 0; j < se->num_members; j++) {
      struct_member_entry* sme = se->members[j];
      PyObject* member = PyObject_GetAttrString(pyobj, sme->name);
      if (member == NULL) { return; }
      PyAutoStruct_SetMember_TypeId(type, out, sme->name, member);
      Py_DECREF(member);
    }
    return;
    
  }
  
  PyErr_Format(PyExc_NameError, "PyAutoStruct: Struct '%s' not registered!", PyAutoType_Name(type));  
  return;
  
}


