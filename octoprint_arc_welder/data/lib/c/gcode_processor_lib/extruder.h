////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Gcode Processor Library
//
// Tools for parsing gcode and calculating printer state from parsed gcode commands.
//
// Copyright(C) 2020 - Brad Hochgesang
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>
struct extruder
{
	extruder();
	double x_firmware_offset;
	double y_firmware_offset;
	double z_firmware_offset;
	double e;
	double e_offset;
	double e_relative;
	double extrusion_length;
	double extrusion_length_total;
	double retraction_length;
	double deretraction_length;
	bool is_extruding_start;
	bool is_extruding;
	bool is_primed;
	bool is_retracting_start;
	bool is_retracting;
	bool is_retracted;
	bool is_partially_retracted;
	bool is_deretracting_start;
	bool is_deretracting;
	bool is_deretracted;
	double get_offset_e() const;
};
