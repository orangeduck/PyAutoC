#include <stdlib.h>
#include <string.h>

#include "PyAutoC.h"

static int hash(const char* s, int size) {
  int h = 0;
  while (*s) h = h * 101 + *s++;
  return abs(h) % size;
}

static PyAutoBucket* PyAutoBucket_New(const char* string, void* item) {
  
  PyAutoBucket* b = malloc(sizeof(PyAutoBucket));
  b->item = item;
  
  b->string = malloc(strlen(string) + 1);
  strcpy(b->string, string);
  
  b->next = NULL;
  b->prev = NULL;
  
  return b;
}

static void PyAutoBucket_Delete(PyAutoBucket* b) {
  if(b->next != NULL) { PyAutoBucket_Delete(b->next); }
  free(b->string);
  free(b);
}

PyAutoHashtable* PyAutoHashtable_New(int size) {

  PyAutoHashtable* ht = malloc(sizeof(PyAutoHashtable));
  
  ht->size = size;
  ht->buckets = malloc( sizeof(PyAutoBucket*) * ht->size );
  
  for(int i = 0; i < size; i++) { ht->buckets[i] = NULL; }
  
  return ht;
}

void PyAutoHashtable_Delete(PyAutoHashtable* ht) {
  for(int i=0; i< ht->size; i++) {
    if (ht->buckets[i] != NULL) {
      PyAutoBucket_Delete(ht->buckets[i]);
    }
  }
  free(ht->buckets);
  free(ht);
}

bool PyAutoHashtable_Contains(PyAutoHashtable* ht, const char* string) {

  if (PyAutoHashtable_Get(ht, string) == NULL) {
    return 0;
  } else {
    return 1;
  }

}

void* PyAutoHashtable_Get(PyAutoHashtable* ht, const char* string) {

  int index = hash(string, ht->size);
  PyAutoBucket* b = ht->buckets[index];
  
  if (b == NULL) {
    return NULL;
  }
  
  while(1){
    if (strcmp(b->string, string) == 0){ return b->item; }
    if (b->next == NULL) { return NULL; }
    else {b = b->next; }
  }
  
  return NULL;

}

void PyAutoHashtable_Set(PyAutoHashtable* ht, const char* string, void* item) {

  int index = hash(string, ht->size);
  PyAutoBucket* b = ht->buckets[index];
  
  if (b == NULL) {
    PyAutoBucket* new_bucket = PyAutoBucket_New(string, item);
    ht->buckets[index] = new_bucket;
    return;
  }
  
  while(1) {
    
    if( strcmp(b->string, string) == 0) {
      b->item = item;
      return;
    }
  
    if( b->next == NULL) {    
      PyAutoBucket* new_bucket = PyAutoBucket_New(string, item);
      b->next = new_bucket;
      new_bucket->prev = b;
      return;
    }
  
    b = b->next;
  }

}

char* PyAutoHashtable_Find(PyAutoHashtable* ht, const void* item) {

  for(int i = 0; i < ht->size; i++) {
    PyAutoBucket* b = ht->buckets[i];
    while (b != NULL) {
      if (b->item == item) { return b->string; }
      b = b->next;
    }
  }
  
  return NULL; 
}

void PyAutoHashtable_Map(PyAutoHashtable* ht, void (*func)(void*)) {

  for(int i = 0; i < ht->size; i++) {
    PyAutoBucket* b = ht->buckets[i];
    while (b != NULL) {
      func(b->item);
      b = b->next;
    }
  }
}

