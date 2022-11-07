#pragma once
#include <Python.h>
#define VPyClass PyObject*
#define VPyFunction PyObject*
#define VPyMethod PyObject*
#define VPyVar PyObject*
#define VPyInt(Name, Value) VPyVar Name = Py_BuildValue("i", Value)
#define VPyFloat VPyVar
#define VPyList VPyVar
#define VPyTuple VPyVar
#define VPyDict VPyVar
#define VPyStr VPyVar
#define DEF static
#define VPySELF PyObject* self
#define VPyArgs PyObject* args
#define STATE static
#define VPyFunctionArray(Name) PyMethodDef Name[]
#define VPyMethodArray(Name) PyMethodDef Name[]
#define VPyFuncFrom(Name) {#Name, Name
#define VPyFuncDocu(Text) Text}
#define INTO ,
#define VPyFuncDEFAULT METH_VARARGS, ""}

DEF VPyFunction buildAInt(VPySELF, VPyArgs) {
	VPyInt(num, 1);
	return num;
}

STATE VPyFunctionArray(FunctionArray) = {
	VPyFuncFrom(buildAInt) INTO VPyFuncDEFAULT
};