#include "PyAutoConvert.h"
#include "PyAutoStruct.h"

typedef struct {
  PyAutoType type;
  int offset;
  char* name;
} struct_member_entry;

typedef struct {
  PyAutoType type_id;
  int num_members;
  int num_reserved_members;
  struct_member_entry* members;
} struct_entry;

struct_entry* struct_entries;
int num_struct_entries = 0;
int num_reserved_struct_entries = 128;

void PyAutoStruct_Initialize() {
  struct_entries = malloc(sizeof(struct_entry) * num_reserved_struct_entries);
}

void PyAutoStruct_Finalize() {
  
  for(int i = 0; i < num_struct_entries; i++) {
    for(int j = 0; j < struct_entries[i].num_members; j++) {
      free(struct_entries[i].members[j].name);
    }
    
    free(struct_entries[i].members);
  }

  free(struct_entries);
}

PyObject* PyAutoStruct_GetMember_TypeId(PyAutoType type, void* cstruct, char* member) {
  
  for(int i = 0; i < num_struct_entries; i++) {
  if (type == struct_entries[i].type_id) {
    struct_entry se = struct_entries[i];
    
    for(int j = 0; j < se.num_members; j++) {
    if (strcmp(se.members[j].name, member) == 0) {
      struct_member_entry sme = se.members[j];
      
      return PyAutoConvert_From_TypeId(sme.type, cstruct+sme.offset);
    }
    }
    
    return PyErr_Format(PyExc_NameError, "PyAutoStruct: Member '%s' not registered for struct '%s'!", member, PyAutoType_Name(type));
    
  }
  }
  
  return PyErr_Format(PyExc_NameError, "PyAutoStruct: Struct '%s' not registered!", PyAutoType_Name(type));
  
}

PyObject* PyAutoStruct_SetMember_TypeId(PyAutoType type, void* cstruct, char* member, PyObject* val) {

  for(int i = 0; i < num_struct_entries; i++) {
  if (type == struct_entries[i].type_id) {
    struct_entry se = struct_entries[i];
    
    for(int j = 0; j < se.num_members; j++) {
    if (strcmp(se.members[j].name, member) == 0) {
      struct_member_entry sme = se.members[j];
      
      PyAutoConvert_To_TypeId(sme.type, val, cstruct+sme.offset);
      if (PyErr_Occurred()) { return NULL; } else { Py_RETURN_NONE; }
    }
    }
    
    return PyErr_Format(PyExc_NameError, "PyAutoStruct: Member '%s' not registered for struct '%s'!", member, PyAutoType_Name(type));
    
  }
  }
  
  return PyErr_Format(PyExc_NameError, "PyAutoStruct: Struct '%s' not registered!", PyAutoType_Name(type));

}

void PyAutoStruct_Register_TypeId(PyAutoType type) {
  
  if (num_struct_entries >= num_reserved_struct_entries) {
    num_reserved_struct_entries += 128;
    struct_entries = realloc(struct_entries, sizeof(struct_entry) * num_reserved_struct_entries);
  }
  
  struct_entry se;
  se.type_id = type;
  se.num_members = 0;
  se.num_reserved_members = 32;
  se.members = malloc(sizeof(struct_member_entry) * se.num_reserved_members);
  
  struct_entries[num_struct_entries] = se;
  num_struct_entries++;
  
}


void PyAutoStruct_RegisterMember_TypeId(PyAutoType type, char* member, PyAutoType member_type, int offset) {

  for(int i = 0; i < num_struct_entries; i++) {
  if (type == struct_entries[i].type_id) {
    
    if (struct_entries[i].num_members >= struct_entries[i].num_reserved_members) {
      struct_entries[i].num_reserved_members += 32;
      struct_entries[i].members = realloc(struct_entries[i].members, sizeof(struct_member_entry) * struct_entries[i].num_reserved_members);
    }
    
    struct_member_entry sme;
    sme.type = member_type;
    sme.offset = offset;
    sme.name = malloc(strlen(member) + 1);
    strcpy(sme.name, member);
    
    struct_entries[i].members[struct_entries[i].num_members] = sme;
    struct_entries[i].num_members++;
    return;
    
  }
  }
  
  PyErr_Format(PyExc_NameError, "PyAutoStruct: Struct '%s' not registered!", PyAutoType_Name(type));
  return;

}

int PyAutoStruct_IsRegistered_TypeId(PyAutoType type) {
  
  for(int i = 0; i < num_struct_entries; i++) {
  if (type == struct_entries[i].type_id) {
    return 1; 
  }
  }
  
  return 0;  
}

PyObject* PyAutoStruct_Convert_From_TypeId(PyAutoType type, void* cstruct) {
  
  for(int i = 0; i < num_struct_entries; i++) {
  if (type == struct_entries[i].type_id) {
    
    PyObject* globals = PyDict_New();
    PyDict_SetItemString(globals, "__builtins__", PyEval_GetBuiltins());
    
    char fmtstring[1024];
    sprintf(fmtstring, "class %s(object): pass\n", PyAutoType_Name(type)); 
    PyObject* ret = PyRun_String(fmtstring, Py_file_input, globals, globals);
    PyObject* new_class = PyDict_GetItemString(globals, PyAutoType_Name(type));
    
    PyObject* args = PyTuple_New(0);
    PyObject* instance = PyObject_Call(new_class, args, NULL);
    Py_DECREF(args);
    
    struct_entry se = struct_entries[i];
    for(int j = 0; j < se.num_members; j++) {
      struct_member_entry sme = se.members[j];
      PyObject* member = PyAutoConvert_From_TypeId(sme.type, cstruct+sme.offset);
      PyObject_SetAttrString(instance, sme.name, member);
      Py_DECREF(member);
      PyErr_Print();
    }
    
    Py_DECREF(ret);
    Py_DECREF(globals);
    
    return instance;
    
  }
  }
  
  return PyErr_Format(PyExc_NameError, "PyAutoStruct: Struct '%s' not registered!", PyAutoType_Name(type));

}

void PyAutoStruct_Convert_To_TypeId(PyAutoType type, PyObject* pyobj, void* out) {

  for(int i = 0; i < num_struct_entries; i++) {
  if (type == struct_entries[i].type_id) {
    
    struct_entry se = struct_entries[i];
    for(int j = 0; j < se.num_members; j++) {
      struct_member_entry sme = se.members[j];
      PyObject* member = PyObject_GetAttrString(pyobj, sme.name);
      PyAutoStruct_SetMember_TypeId(type, out, sme.name, member);
      Py_DECREF(member);
    }
    
  }
  }
  
  PyErr_Format(PyExc_NameError, "PyAutoStruct: Struct '%s' not registered!", PyAutoType_Name(type));  
  return;
  
}


