////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Gcode Processor Library
//
// Tools for parsing gcode and calculating printer state from parsed gcode commands.
//
// Copyright(C) 2020 - Brad Hochgesang
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef PARSED_COMMAND_PARAMETER_H
#define PARSED_COMMAND_PARAMETER_H
#include <string>
struct parsed_command_parameter
{
public:
	parsed_command_parameter();
	~parsed_command_parameter();
	parsed_command_parameter(std::string name, double value);
	parsed_command_parameter(std::string name, std::string value);
	parsed_command_parameter(std::string name, unsigned long value);
	std::string name;
	char value_type;
	double double_value;
	unsigned long unsigned_long_value;
	std::string string_value;
};

#endif
