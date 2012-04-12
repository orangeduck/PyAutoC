PyAutoC
=======


Introduction
------------

PyAutoC automatically wraps C functions and structs so that they can be called effortlessly from the Python/C API.

If you have a large C codebase and don't feel like writing wrappers around every function, PyAutoC can help significantly.
If you have a Python-C Interop which you want to be easily extendable by others at run-time, PyAutoC can also help!


Basic Function Usage
-------------------- 
    
	#include "Python.h"
	#include "PyAutoC.h"
	
    static float add_numbers(int first, float second) {
      return first + second;
    }
    
    int main() {
      
      Py_Initialize();
      
      PyAutoConvert_RegisterPrimatives();
      PyAutoFunc_Register_Args2(add_numbers, float, int, float);
  
      PyObject* args0 = Py_BuildValue("(if)", 5, 6.13);
      PyObject* result0 = PyAutoFunc_Call(add_numbers, args0);
      
	  Py_DECREF(result0); Py_DECREF(args0);
      Py_Finalize();
      
      return 0;
      
    }

	
Basic Struct Usage
------------------ 

    typedef struct {
      float x, y, z;
    } vector3;
    
    PyAutoStruct_Register(vector3);
    PyAutoStruct_RegisterMember(vector3, x, float);
    PyAutoStruct_RegisterMember(vector3, y, float);
    PyAutoStruct_RegisterMember(vector3, z, float);
    
    vector3 position = {1.0f, 2.11f, 3.16f};
    
    PyObject* result2 = PyAutoStruct_Get(vector3, &position, y);
    PyObject_PrintStdout(result2);
    Py_DECREF(result2);

	
PyAutoStructs are very similar to their functional counterparts. As with PyAutoFunctions, they can be accessed at run-time and do automatic conversion of types. This access can come either in the form of a reference to a member (function pointer for PyAutoFuncs) or as a string. This makes them a powerful tool which can be used dynamically at run time.

	
Extended Usage
--------------

Because PyAutoC lets you register new Python accessible functions at run time it is perfect for automatically wrapping Python Classes. For example by overriding __getattr__ and __setattr__ of some Python class we can make a Python object that behaves as if it were a C struct.

    import pyautoc_demo
    
    class cstruct(object):
	    def __getattr__(self, attr): pyautoc_demo.get_attr(self, attr)
		def __setattr__(self, attr, val): pyautoc_demo.set_attr(self, attr, val)

		
Then in the C API you can write something that looks like this.
    
	
    static PyObject* get_attr(PyObject* unused, PyObject* args) {
        PyObject* self = PyTuple_GetItem(args, 0);
		PyObject* attr = PyTuple_GetItem(args, 1);
		
		void* cstruct = somehow_get_ptr(self);
		PyAutoType type = somehow_get_type(self);
		return PyAutoStruct_GetByName_TypeId(type, cstruct, PyString_AsString(attr));
    }
	
    static PyObject* set_attr(PyObject* unused, PyObject* args) {
        PyObject* self = PyTuple_GetItem(args, 0);
		PyObject* attr = PyTuple_GetItem(args, 1);
		PyObject* val = PyTuple_GetItem(args, 2);
		
		void* cstruct = somehow_get_ptr(self);
		PyAutoType type = somehow_get_type(self);
		PyAutoStruct_SetByName_TypeId(type, cstruct, PyString_AsString(attr), val);
		Py_RETURN_NONE;
    }
	
    static PyMethodDef method_table[] = {
        {"get_attr", get_attr, METH_VARARGS, ""},
        {"set_attr", set_attr, METH_VARARGS, ""},
        {NULL, NULL, 0, NULL},
    };
	
	Py_InitModule("pyautoc_demo", method_table);
	

For the "somehow_get_type" function you can often store some information in the Python Object Instance which distinguishes itself. A trick I like to use is to look at the ".__class__.__name__" property of the instance and feed it into the function "PyAutoType_Register". This spits out a PyAutoType and if the input string matches that of registered struct then it will return the same PyAutoType!

For "somehow_get_ptr" there are lots of options. It is possible to store C pointers using something like "PyCObject_FromVoidPtr", but I like to just store a string which identifies the instance and then look this string up in C using a dictionary or similar to find the actual pointer.

The above technique can also be easily extended so that as well as members, the class is able to look up methods too!


New Argument Types
------------------

To call functions or access struct members which have non-primitive types it is possible to register your own conversion functions.

    typedef struct {
        int x, y;
    } pair;
    
    static PyObject* convert_from_pair(void* data) {
        pair p = *(pair*)data;
        return Py_BuildValue("(ii)", p.x, p.y);
    }
	
    void convert_to_pair(PyObject* pyobj, void* out) {
        pair* p = (pair*)out;
        p->x = PyInt_AsLong(PyTuple_GetItem(pyobj, 0));
        p->y = PyInt_AsLong(PyTuple_GetItem(pyobj, 1));
    }
	
	PyAutoConvert_Register(pair, convert_from_pair, convert_to_pair);
	
Now it is possible to call any functions with 'pair' as an argument or return type and PyAutoC will handle any conversions automatically. This also works for structs and you can even use the registered functions directly in your code by using PyAutoConvert.

	pair p = {1, 2};
    PyObject* pypair = PyAutoConvert_From(pair, &p);  


	
Issues
------

Using PyAutoC creates a small memory and performance overhead. This is because it duplicates much of the process involved in managing the stack such as copying stack data. It also uses function pointers which cannot be inlined, so sometimes converting a lot of Python data to C data can be slower than if the process is declared statically.

Secondly the function registration macros are a little verbose. The argument count must be specified in the name and also if the function returns void.

    PyAutoFunc_Register_Args2(add_numbers, float, int, float);
    PyAutoFunc_Register_Void_Args3(message_ntimes, void, char*, int);
	
Finally there is hard coded limit to many aspects such as number of conversion functions which can be registered or maximum number of arguments in registered functions. This can be increased with some simple edits to the source and recompiling, but it increases memory overheads.
