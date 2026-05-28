////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Arc Welder: Anti-Stutter Python Extension for the OctoPrint Arc Welder plugin.
//
// Compresses many G0/G1 commands into G2/G3(arc) commands where possible, ensuring the tool paths stay within the specified resolution.
// This reduces file size and the number of gcodes per second.
//
// Copyright(C) 2020 - Brad Hochgesang
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <arc_welder.h>
#include <string>
#include "py_logger.h"
#ifdef _DEBUG
#undef _DEBUG
#include <Python.h>
#define _DEBUG
#else
#include <Python.h>
#endif
class py_arc_welder : public arc_welder
{
public:
	py_arc_welder(std::string source_path, std::string target_path, py_logger* logger, double resolution_mm, double max_radius, bool g90_g91_influences_extruder, int buffer_size, PyObject* py_progress_callback):arc_welder(source_path, target_path, logger, resolution_mm, max_radius, g90_g91_influences_extruder, buffer_size)
	{
		py_progress_callback_ = py_progress_callback;
	}
	virtual ~py_arc_welder() {

	}
	static PyObject* build_py_progress(const arc_welder_progress& progress);
protected:
	virtual bool on_progress_(const arc_welder_progress& progress);
private:
	PyObject* py_progress_callback_;
};
