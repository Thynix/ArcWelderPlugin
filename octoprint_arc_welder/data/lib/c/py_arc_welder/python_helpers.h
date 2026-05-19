////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Arc Welder: Anti-Stutter Python Extension for the OctoPrint Arc Welder plugin.
//
// Compresses many G0/G1 commands into G2/G3(arc) commands where possible, ensuring the tool paths stay within the specified resolution.
// This reduces file size and the number of gcodes per second.
//
// Copyright(C) 2020 - Brad Hochgesang
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#ifdef _DEBUG
#undef _DEBUG
#include <Python.h>
#define _DEBUG
#else
#include <Python.h>
#endif
#include <string>
namespace gcode_arc_converter {
	int PyUnicode_SafeCheck(PyObject* py);
	const char* PyUnicode_SafeAsString(PyObject* py);
	PyObject* PyString_SafeFromString(const char* str);
	PyObject* PyUnicode_SafeFromString(std::string str);
	double PyFloatOrInt_AsDouble(PyObject* py_double_or_int);
	long PyIntOrLong_AsLong(PyObject* value);
	bool PyFloatLongOrInt_Check(PyObject* value);
}
