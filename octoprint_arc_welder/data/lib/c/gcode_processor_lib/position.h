////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Gcode Processor Library
//
// Tools for parsing gcode and calculating printer state from parsed gcode commands.
//
// Copyright(C) 2020 - Brad Hochgesang
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef POSITION_H
#define POSITION_H
#include <string>
#include "parsed_command.h"
#include "extruder.h"


struct position
{
	position();
	position(int extruder_count);
	position(const position &pos); // Copy Constructor
	virtual ~position();
	position& operator=(const position& pos);
	std::string to_string(bool rewrite, bool verbose, std::string additional_comment);
	void reset_state();
	parsed_command command;
	int feature_type_tag;
	double f;
	bool f_null;
	double x;
	bool x_null;
	double x_offset;
	double x_firmware_offset;
	bool x_homed;
	double y;
	bool y_null;
	double y_offset;
	double y_firmware_offset;
	bool y_homed;
	double z;
	bool z_null;
	double z_offset;
	double z_firmware_offset;
	bool z_homed;
	bool is_metric;
	bool is_metric_null;
	double last_extrusion_height;
	bool last_extrusion_height_null;
	long layer;
	double height;
	int height_increment;
	int height_increment_change_count;
	bool is_printer_primed;
	bool has_definite_position;
	double z_relative;
	bool is_relative;
	bool is_relative_null;
	bool is_extruder_relative;
	bool is_extruder_relative_null;
	bool is_layer_change;
	bool is_height_change;
	bool is_height_increment_change;
	bool is_xy_travel;
	bool is_xyz_travel;
	bool is_zhop;
	bool has_position_changed;
	bool has_xy_position_changed;
	bool has_received_home_command;
	bool is_in_position;
	bool in_path_position;
	long file_line_number;
	long gcode_number;
	long file_position;
	bool gcode_ignored;
	bool is_in_bounds;
	bool is_empty;
	int current_tool;
	int num_extruders;
	bool has_been_deleted;
	extruder * p_extruders;
	extruder& get_current_extruder() const;
	extruder& get_extruder(int index) const;
	void set_num_extruders(int num_extruders_);
	void delete_extruders();
	double get_gcode_x() const;
	double get_gcode_y() const;
	double get_gcode_z() const;
	void set_xyz_axis_mode(const std::string& xyz_axis_default_mode);
	void set_e_axis_mode(const std::string& e_axis_default_mode);
	void set_units_default(const std::string& units_default);
	bool can_take_snapshot();
};
#endif
