PyAutoC
=======

Version 0.8

Introduction
------------

PyAutoC automatically wraps C functions and structs at runtime so that they can be called from the Python/C API.

* Don't fancy the idea of hand wrapping every function and struct in your codebase?
* Don't like the look of the monster that is SWIG?
* Want a way for developers to register extra functionality at runtime?

PyAutoC is here to help.


Basic Usage 1
-------------
    
```c
#include "Python.h"
#include "PyAutoC.h"

static float add_numbers(int first, float second) {
  return first + second;
}

int main(int argc, char **argv) {

  Py_Initialize();
  PyAutoC_Initialize();

  PyAutoFunction_Register(add_numbers, float, 2, int, float);

  PyObject* args = Py_BuildValue("(if)", 5, 6.13);
  PyObject* result = PyAutoFunction_Call(add_numbers, args);
  PyObject_Print(result, stdout, 0);
  Py_DECREF(result); Py_DECREF(args);

  PyAutoC_Finalize();
  Py_Finalize();

  return 0;
}
```
	
PyAutoC will call `add_numbers` with values converted from their Python counterparts. It will then convert the return value back into a Python Object. No editing of the original function required.

	
Basic Usage 2
-------------

```c
#include "Python.h"
#include "PyAutoC.h"

typedef struct {
  float x, y, z;
} vector3;

int main(int argc, char **argv) {

  Py_Initialize();
  PyAutoC_Initialize();

  PyAutoStruct_Register(vector3);
  PyAutoStruct_RegisterMember(vector3, x, float);
  PyAutoStruct_RegisterMember(vector3, y, float);
  PyAutoStruct_RegisterMember(vector3, z, float);

  vector3 position = {1.0f, 2.11f, 3.16f};
  PyObject* mem_y = PyAutoStruct_Get(vector3, &position, y);
  PyObject_Print(mem_y, stdout, 0);
  Py_DECREF(mem_y);

  PyAutoC_Finalize();
  Py_Finalize();

  return 0;
}
```
	
Structs work similarly to their functional counterparts. They can be accessed at runtime and do automatic conversion of types.
 

Type Conversions
----------------

To call functions or access struct members which have non-primitive types it is possible to register your own conversion functions.

```c
typedef struct {
  int x, y;
} pair;

static PyObject* convert_from_pair(const void* data) {
  pair p = *(pair*)data;
  return Py_BuildValue("(ii)", p.x, p.y);
}

static void convert_to_pair(PyObject* pyobj, void* out) {
  pair* p = (pair*)out;
  p->x = PyInt_AsLong(PyTuple_GetItem(pyobj, 0));
  p->y = PyInt_AsLong(PyTuple_GetItem(pyobj, 1));
}

PyAutoConvert_Register(pair, convert_from_pair, convert_to_pair);
```

Now it is possible to call any functions with `pair` as an argument or return type and PyAutoC will handle any conversions automatically. You can also use the registered functions directly in your code by using PyAutoConvert.

```c
pair p = {1, 2};
PyObject* pypair = PyAutoConvert_From(pair, &p);
```

Alternatively, when you register structs with PyAutoC, if no conversion functions are known, it will attempt to automatically convert them. One word of warning - be careful with circular references. The conversion is recursive and given the chance will happily run forever!

```c
typedef struct {
  char* first_name;
  char* second_name;
  float coolness;
} person_details;

PyAutoStruct_Register(person_details);
PyAutoStruct_RegisterMember(person_details, first_name, char*);
PyAutoStruct_RegisterMember(person_details, second_name, char*);
PyAutoStruct_RegisterMember(person_details, coolness, float);

person_details my_details = {"Daniel", "Holden", 125212.213};
PyObject* py_details = PyAutoConvert_From(person_details, &my_details);
PyObject* py_first_name = PyObject_GetAttrString(py_details, "first_name");
PyObject_Print(py_first_name, stdout, 0);

Py_DECREF(py_first_name);
Py_DECREF(py_details);
```

Using C headers
--------------------

I've included a basic python script which will autogenerate PyAutoC code for structs and functions from C headers.

```
$ python autogen.py ../Corange/include/assets/sound.h

PyAutoStruct_Register(sound);
PyAutoStruct_RegisterMember(sound, data, char*);
PyAutoStruct_RegisterMember(sound, length, int);

PyAutoFunction_Register(wav_load_file, sound*, 1, char*);
PyAutoFunction_RegisterVoid(sound_delete, 1, sound*);

```

Extended Usage 1
----------------

You can use PyAutoC to very quickly and easily create Python C modules for a bunch of functions such as might be done via SWIG or similar.

```c
#include "Python.h"
#include "PyAutoC.h"

static float add_numbers(int first, float second) {
  return first + second;
}

static void hello_world(char* person) {
  printf("Hello %s!", person);
}

static PyObject* call(PyObject* unused, PyObject* args) {
  PyObject* func = PyTuple_GetItem(args, 0);
  PyObject* fargs = PyTuple_GetSlice(args, 1, PyTuple_Size(args));
  PyObject* ret = PyAutoFunction_CallByName(PyString_AsString(func), fargs);
  Py_DECREF(fargs);
  return ret;
}

static PyMethodDef method_table[] = {
  {"call", call, METH_VARARGS, ""},
  {NULL, NULL, 0, NULL},
};

PyMODINIT_FUNC initpyautoc_demo(void) {
  PyAutoC_Initialize();
  Py_AtExit(PyAutoC_Finalize);

  PyAutoFunction_Register(add_numbers, float, 2, int, float);	
  PyAutoFunction_RegisterVoid(hello_world, 1, char*);	

  Py_InitModule("pyautoc_demo", method_table);
}
```

Then in Python...

```python
import pyautoc_demo
pyautoc_demo.call("add_numbers", 5, 6.13);
pyautoc_demo.call("hello_world", "Daniel");
```

Once you have this basic interface it is easy to integrate more complicated and transparent APIs with some more complicated Python.


Runtime?
--------

Many developers like to wrap their libraries externally before compile time using programs such as SWIG. This approach has many benefits but can be somewhat brittle and lacking in control. PyAutoC takes a different approach by storing type information and doing conversions and anything else needed at runtime. As well as being a more controlled approach this also allows for some interesting options for dynamic behaviour.

When normally building a Python/C extension all accessible functions must be statically declared in a methods table and compiled. If a developer wants to add more functions to the Python Bindings he must add more methods to the table. Using PyAutoC, users and developers can register new functions, structs and type conversions _as the program is running_. This means developers can use and extend your Python API without ever touching a PyObject!

It also means that the job of wrapping is much easier - you can use strings and dynamic elements directly from Python. For example...


Extended Usage 2
----------------

PyAutoC is perfect for automatically wrapping existing C Structs as Python classes. By overriding `__getattr__` and `__setattr__` of a class we can easily make a Python object that behaves as if it were a C struct.

```python
import birdie

class python_birdie(object):
    def __getattr__(self, attr): return birdie.get_attr(self, attr)
    def __setattr__(self, attr, val): return birdie.set_attr(self, attr, val)
	
bird = python_birdie()
print bird.name
print bird.num_wings
	
```
		
Then in the C API you can write something that looks like this.
    
```c
typedef struct {
  char* name;
  int num_wings;
} birdie;

static PyObject* birdie_get_attr(PyObject* unused, PyObject* args) {
  PyObject* self = PyTuple_GetItem(args, 0);
  PyObject* attr = PyTuple_GetItem(args, 1);

  birdie* bird = get_instance_ptr(self);
  return PyAutoStruct_GetMember(birdie, bird, PyString_AsString(attr));
}

static PyObject* birdie_set_attr(PyObject* unused, PyObject* args) {
  PyObject* self = PyTuple_GetItem(args, 0);
  PyObject* attr = PyTuple_GetItem(args, 1);
  PyObject* val = PyTuple_GetItem(args, 2);

  birdie* bird = get_instance_ptr(self);
  return PyAutoStruct_SetMember(birdie, bird, PyString_AsString(attr), val);
}

static PyMethodDef method_table[] = {
  {"get_attr", birdie_get_attr, METH_VARARGS, ""},
  {"set_attr", birdie_set_attr, METH_VARARGS, ""},
  {NULL, NULL, 0, NULL},
};

PyAutoStruct_Register(birdie);
PyAutoStruct_RegisterMember(birdie, name, char*);
PyAutoStruct_RegisterMember(birdie, num_wings, int);

Py_InitModule("birdie", method_table);
```

A lot less work than writing a bunch of getters and setters!

The `get_instance_ptr` function is left for the user to implement and there are lots of options. The idea is that somehow the python instance should tell you how to get a pointer to the actual struct instance in C which it represents. One option is to store C pointers in the python instance using something like `PyCObject_FromVoidPtr`. An alternative I like is to just store a string in the python instance which uniquely identifies it. Once you have this, in C it is possible to just look this string up in a dictionary or similar to find the actual pointer.

For fun why not try also overriding `__init__` and `__del__` to call some C functions which allocate and decallocate the structure you are emulating, storing some data to let you identify the instance later. It is also easy to extend the above technique so that, as well as members, the class is able to look up and execute methods!

The true power of PyAutoC comes if you look a level deeper. If you use `PyAutoStruct_GetMember_TypeId` or `PyAutoStruct_SetMember_TypeId` you can even extend the above code to work for arbritary structs/classes which developers can add to.

For this to work you need to somehow get a PyAutoType value. This can be found by feeding a string into `PyAutoType_Find`. The `PyAutoType_Find` function will lookup a string and see if a type has been registered with the same name. This means that if you give it a string of a previously registered data type E.G `birdie`, it will return a matching Id. One trick I like it to use is to feed into it the `.__class__.__name__` property of a python instance. This means that I can create a new python class with overwritten `__getattr__` and `__setattr__` it will automatically act like the corresponding C struct with the same name.
	
Managing Behaviour
------------------

Often in C, the same types can have different meanings. For example an `int*` could either mean that a function wants an array of integers or that it outputs some integer. We can change the behaviour of PyAutoC without changing the function signature by using typedefs and new conversion functions. Then on function registration you just use the newly defined type rather than the old one. Providing the types are truely the same there wont be any problems with converting types or breaking the artificial stack.

```c

static void print_int_list(int* list, int num_ints) {
  for(int i = 0; i < num_ints; i++) {
    printf("Int %i: %i\n", i, list[i]);
  }
}

typedef int* int_list;

static int list_space[512];
static void convert_to_int_list(PyObject* pyobj, void* out) {
  for(int i = 0; i < PyList_Size(pyobj); i++) {
    list_space[i] = PyInt_AsLong(PyList_GetItem(pyobj, i));
  }
  *(int_list*)out = list_space;
}

PyAutoConvert_RegisterTo(int_list, convert_to_int_list);

PyAutoFunction_RegisterVoid(print_int_list, 2, int_list, int);

```

As you can probably see, automatic wrapping and type conversion becomes hard when memory management and pointers are involved. I'm looking at ways to improve this, perhaps with the ability to register 'before' and 'after' methods for certain functions or conversions.

FAQ
---

* How do unions work?

  They work the same way as structs. All the PyAutoStruct functions should be fine to use on them. Like in C though, accessing them "incorrectly" in python will result in the raw data being interpreted differently. PyAutoC doesn't do any clever checking for you.
  
* How do enums work?

  Enums work like any other type and the best way to deal with them is to write an explicit conversion function. There is no real way to know what storage type compilers will pick for an enum, it could be a unsigned char, signed int, long or anything else. If though, you are sure what storage type the compiler is using for a particular enum, it might be easier to just use that as the registered type and get a conversion for free.

* How do const types work?

  Const types should ultimately be treated as their own unique type with custom conversion functions. But, similarly to enums, if you are careful it is often possible to reuse conversion functions you have written for non-const variations without any negative effects.
  
* How do I handle errors?
  
  Error handling is done via Python Exceptions. When in C, if a function returns, it returns NULL on an error. Otherwise use PyErr_Occurred(). When writing your own conversion functions it is best to propagate errors outward in a similar way.

* Does this work on Linux/Mac/Windows?
  
  On Linux, yes. On Mac, probably but I don't have one to test on. On Windows, yes under MinGW or Cygwin. The binaries and headers will also link and compile under Visual Studio (in C++ mode).
  
  I've done some experiments getting Lua AutoC to _compile_ under Visual Studio and the port is fairly simple but there are a couple of annoying aspects. If someone is interested I'll be more than happy to share my developments but for now I would rather keep the code in the repo clean.

* Is PyAutoC slow?
  
  For most uses PyAutoC has to lookup runtime information in a hashtable. For calling functions it has to duplicate some of the process involved in managing the stack. Perhaps for a very large codebase there might be some overhead in performance and memory but for any normal sized one, this is minimal compared to the internal workings of the Python/C API. If you are concerned about performance you can still wrap your functions manually but perhaps if you are using a scripting language like python it isn't much bother.

* Is this just macro hacks? Can I really use it with my production code?

  There are certainly some macro tricks going on, but most of them are pretty simple and nothing to gruesome - they are just there to save you typing. I use it to wrap my game engine Corange (~10000 LOC, ~1000 functions) without any issues. If you are worried send me an email and I'll explain the internals so that you can decide for yourself.
  
  