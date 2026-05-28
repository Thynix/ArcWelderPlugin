////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Gcode Processor Library
//
// Tools for parsing gcode and calculating printer state from parsed gcode commands.
//
// Copyright(C) 2020 - Brad Hochgesang
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "extruder.h"
#include <iostream>

extruder::extruder()
{
	x_firmware_offset = 0;
	y_firmware_offset = 0;
	z_firmware_offset = 0;
	e = 0;
	e_offset = 0;
	e_relative = 0;
	extrusion_length = 0;
	extrusion_length_total = 0;
	retraction_length = 0;
	deretraction_length = 0;
	is_extruding_start = false;
	is_extruding = false;
	is_primed = false;
	is_retracting_start = false;
	is_retracting = false;
	is_retracted = false;
	is_partially_retracted = false;
	is_deretracting_start = false;
	is_deretracting = false;
	is_deretracted = false;
}

double extruder::get_offset_e() const
{
	return e - e_offset;
}
