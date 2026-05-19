////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Gcode Processor Library
//
// Tools for parsing gcode and calculating printer state from parsed gcode commands.
//
// Copyright(C) 2020 - Brad Hochgesang
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef PARSED_COMMAND_H
#define PARSED_COMMAND_H
#include <string>
#include <vector>
#include "parsed_command_parameter.h"

struct parsed_command
{
public:
	parsed_command();
	std::string command;
	std::string gcode;
	std::string comment;
	bool is_empty;
	bool is_known_command;
	std::vector<parsed_command_parameter> parameters;
	void clear();
	std::string to_string();
	std::string rewrite_gcode_string();
};

#endif
