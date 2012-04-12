#include "PyAutoError.h"
#include "PyAutoConvert.h"
#include "PyAutoStruct.h"

#define MAX_NAME_LEN 256
#define MAX_MEM_ENTRIES 20
#define MAX_STRUCT_ENTRIES 512

typedef struct {
  PyAutoType type;
  int offset;
  char name[MAX_NAME_LEN];
} struct_member_entry;

typedef struct {
  PyAutoType type_id;
  int num_members;
  struct_member_entry members[MAX_MEM_ENTRIES];
} struct_entry;

struct_entry struct_entries[MAX_STRUCT_ENTRIES];
int num_struct_entries = 0;

PyObject* PyAutoStruct_GetByOffset_TypeId(PyAutoType type, void* cstruct, PyAutoType member_type, int offset) {

  for(int i = 0; i < num_struct_entries; i++) {
  if (type == struct_entries[i].type_id) {
    struct_entry se = struct_entries[i];
    return PyAutoConvert_From_TypeId(member_type, cstruct+offset);
  }
  }
  
  PyAutoError("Struct '%s' not registered!", PyAutoType_Name(type));

}

PyObject* PyAutoStruct_GetByName_TypeId(PyAutoType type, void* cstruct, char* member) {
  
  for(int i = 0; i < num_struct_entries; i++) {
  if (type == struct_entries[i].type_id) {
    struct_entry se = struct_entries[i];
    
    for(int j = 0; j < se.num_members; j++) {
    if (strcmp(se.members[j].name, member) == 0) {
      struct_member_entry sme = se.members[j];
      
      return PyAutoConvert_From_TypeId(sme.type, cstruct+sme.offset);
    }
    }
    
    PyAutoError("Member '%s' not registered for struct '%s'!", member, PyAutoType_Name(type));
    
  }
  }
  
  PyAutoError("Struct '%s' not registered!", PyAutoType_Name(type));
  
}

void PyAutoStruct_SetByName_TypeId(PyAutoType type, void* cstruct, char* member, PyObject* val) {

  for(int i = 0; i < num_struct_entries; i++) {
  if (type == struct_entries[i].type_id) {
    struct_entry se = struct_entries[i];
    
    for(int j = 0; j < se.num_members; j++) {
    if (strcmp(se.members[j].name, member) == 0) {
      struct_member_entry sme = se.members[j];
      
      return PyAutoConvert_To_TypeId(sme.type, val, cstruct+sme.offset);
    }
    }
    
    PyAutoError("Member '%s' not registered for struct '%s'!", member, PyAutoType_Name(type));
    
  }
  }
  
  PyAutoError("Struct '%s' not registered!", PyAutoType_Name(type));

}

void PyAutoStruct_Register_TypeId(PyAutoType type) {
  
  if (num_struct_entries >= MAX_STRUCT_ENTRIES) {
    PyAutoError("Maximum struct entries of %i reached!", MAX_STRUCT_ENTRIES);
  }
  
  struct_entry se;
  se.type_id = type;
  se.num_members = 0;
  
  struct_entries[num_struct_entries] = se;
  num_struct_entries++;
  
}


void PyAutoStruct_RegisterMember_TypeId(PyAutoType type, char* member, PyAutoType member_type, int offset) {

  for(int i = 0; i < num_struct_entries; i++) {
  if (type == struct_entries[i].type_id) {
    struct_entry se = struct_entries[i];
    
    if (se.num_members >= MAX_MEM_ENTRIES) {
      PyAutoError("Maximum member entries of %i for struct '%s' reached!", MAX_MEM_ENTRIES, PyAutoType_Name(type));
    }
    
    if (strlen(member) >= MAX_NAME_LEN) {
      PyAutoError("Member name '%s' is longer than maximum of %i characters!", member, MAX_NAME_LEN);
    }
    
    struct_member_entry sme;
    sme.type = member_type;
    sme.offset = offset;
    strcpy(sme.name, member);
    
    struct_entries[i].members[se.num_members] = sme;
    struct_entries[i].num_members++;
    return;
    
  }
  }
  
  PyAutoError("Struct '%s' not registered!", PyAutoType_Name(type));

}