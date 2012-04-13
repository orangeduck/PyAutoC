PyAutoC
=======


Introduction
------------

PyAutoC automatically wraps C functions and structs at runtime so that they can be called from the Python/C API.

* Don't fancy the idea of hand wrapping every function and struct in your codebase?
* Don't like the look of the monster that is SWIG?
* Want a way for developers to register extra functionality at runtime?

PyAutoC is here to help.


Basic Function Usage
-------------------- 
    
```c
#include "Python.h"
#include "PyAutoC.h"

static float add_numbers(int first, float second) {
	return first + second;
}

int main(int argc, char **argv) {
  
	Py_Initialize();
	PyAutoC_Initialize();

	PyAutoFunction_RegisterArgs2(add_numbers, float, int, float);

	PyObject* args = Py_BuildValue("(if)", 5, 6.13);
	PyObject* result = PyAutoFunction_Call(add_numbers, args);
	PyObject_Print(result, stdout, 0);
	Py_DECREF(result); Py_DECREF(args);

	PyAutoC_Finalize();
	Py_Finalize();

	return 0;
}
```
	
PyAutoC will call __add\_numbers__ with values converted from their Python counterparts. It will then convert the return value back into a Python Object. No editing of the original function required.

	
Basic Struct Usage
------------------ 

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
	PyObject* y = PyAutoStruct_Get(vector3, &position, y);
	PyObject_Print(y, stdout, 0);
	Py_DECREF(y);
	
    PyAutoC_Finalize();
	Py_Finalize();
	
	return 0;
}
```
	
Structs work similarly to their functional counterparts. They can be accessed at runtime and do automatic conversion of types.

New Argument Types
------------------

To call functions or access struct members which have non-primitive types it is possible to register your own conversion functions.

```c
typedef struct {
	int x, y;
} pair;

static PyObject* convert_from_pair(void* data) {
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

Now it is possible to call any functions with __pair__ as an argument or return type and PyAutoC will handle any conversions automatically. You can also use the registered functions directly in your code by using PyAutoConvert.

```c
pair p = {1, 2};
PyObject* pypair = PyAutoConvert_From(pair, &p);
```

Runtime?
--------

When normally building a Python/C extension all accessible functions must be statically declared in a methods table and compiled. Using PyAutoC, users and developers can register new functions, structs and type conversion _as the program is running_. This means you can essentially create a set of tools which let other developers extend what is accessible from Python just by writing their own C functions and structs.

It can also mean that lots of your job is cut out by using strings and dynamic elements from python, as shown below...


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
  
	PyAutoFunction_RegisterArgs2(add_numbers, float, int, float);	
	PyAutoFunction_RegisterArgs1Void(hello_world, void, char*);	

    Py_InitModule("pyautoc_demo", method_table);
}
```

Then in Python...

```python
import pyautoc_demo
pyautoc_demo.call("add_numbers", 5, 6.13);
pyautoc_demo.call("hello_world", "Daniel");
```

Once you have this basic interface it is easy to intergrate more complicated and transparent APIs with some more complicated Python. For Example...

Extended Usage 2
----------------

Because PyAutoC lets you register and access new Python functions at run time it is perfect for automatically wrapping existing C Structs as Python classes. By overriding __\_\_getattr____ and __\_\_setattr____ of a class we can easily make a Python object that behaves as if it were a C struct.

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

The __get\_instance\_ptr__ function is left for the user to implement and there are lots of options. The idea is that somehow the python instance should tell you how to get a pointer to the actual struct instance in C which it represents. One option is to store C pointers in the python instance using something like __PyCObject\_FromVoidPtr__. An alternative I like is to just store a string in the python instance which uniquely identifies it. Once you have this, in C it is possible to just look this string up in a dictionary or similar to find the actual pointer.

For fun why not try also overriding __\_\_init____ and __\_\_del____ to call some C functions which allocate and decallocate the structure you are emulating, storing some data to let you identify the instance later. It is also easy to extend the above technique so that, as well as members, the class is able to look up and execute methods!

The true power of PyAutoC comes if you look a level deeper. If you use __PyAutoStruct\_GetMember\_TypeId__ or __PyAutoStruct\_SetMember\_TypeId__ you can even extend the above code to work for arbritary structs/classes which developers can add to.

For this to work you need to somehow get a PyAutoType value. This can be found by feeding a string into __PyAutoType\_Register__. The __PyAutoType\_Register__ function is a simple function which gives a unique identifier to each new string it encounters. Run time type-ids are generated for types in this way - the macro preprocessor just turns the token into a string and feeds it into this function. This means that if you give it a string of a previously registered data type it will return a matching Id. One trick I like it to use is to feed into it the __.\_\_class\_\_.\_\_name____ property of a python instance. This means that I can create a new python class with overwritten __\_\_getattr____ and __\_\_setattr____ it will automatically act like the corrisponding C struct with the same name - providing it has been registered by some developer.
	
Managing Behaviour
------------------

Often in C, the same types can have different meanings. For example an int* could either mean that a function wants an array of integers or that it outputs some integer. We can change the behaviour of PyAutoC without changing the function signature by using typedefs and new conversion functions. Then on function registration you just use the newly defined type rather than the old one. Providing the types are truely the same there wont be any problems with converting types or breaking the artificial stack.

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

PyAutoFunction_RegisterArgs2Void(print_int_list, void, int_list, int);

```

As you can probably see, automatic wrapping and type conversion becomes hard when memory management and pointers are involved. I'm looking at ways to improve this, perhaps with the ability to register 'before' and 'after' methods for certain functions or conversions.

Warnings/Issues
---------------

* The handling of errors is done via Python Exceptions. Checking for them in C is important or you'll probably end up with a segfault or garbage values.

* I've not yet managed to get PyAutoC to compile using MSVS and due to the heavy macro use and lack of C99 I don't know if I can. Until I look into it more, compile any extensions under windows with MinGW and it will probably be okay.

* The function registration macros are a little verbose and limited though this is unavoidable. Always remember that the argument count must be specified in the name and also if the function returns void.

```c
PyAutoFunction_RegisterArgs2(add_numbers, float, int, float);
PyAutoFunction_RegisterArgs3Void(add_numbers_message, void, char*, int, float);
```
	
* Using PyAutoC for functions creates a small memory and performance overhead. This is because it duplicates much of the process involved in managing the stack such as copying stack data. Because most of the logic happens at run-time it also uses a lot of function pointers. These cannot be optimised and inlined very easily so processes such as converting lots of Python data to C data can be slower than if the process is declared statically. Still, the overhead is fairly minimal and if you are wrapping with a scripting language like python then perhaps it is less of a concern.

