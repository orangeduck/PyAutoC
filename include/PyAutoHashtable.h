#ifndef PyAutoHashtable_h
#define PyAutoHashtable_h

struct PyAutoBucket {
  void* item;
  char* string;
  struct PyAutoBucket* next;
  struct PyAutoBucket* prev;
};

struct PyAutoBucket;
typedef struct PyAutoBucket PyAutoBucket;

typedef struct {
  PyAutoBucket** buckets;
  int size;
} PyAutoHashtable;


PyAutoHashtable* PyAutoHashtable_New(int table_size);
void PyAutoHashtable_Delete(PyAutoHashtable* ht);

int PyAutoHashtable_Contains(PyAutoHashtable* ht, char* string);
void* PyAutoHashtable_Get(PyAutoHashtable* ht, char* string);
void PyAutoHashtable_Set(PyAutoHashtable* ht, char* string, void* item);

char* PyAutoHashtable_Find(PyAutoHashtable* ht, void* item);

void PyAutoHashtable_Map(PyAutoHashtable* ht, void (*func)(void*));

#endif
