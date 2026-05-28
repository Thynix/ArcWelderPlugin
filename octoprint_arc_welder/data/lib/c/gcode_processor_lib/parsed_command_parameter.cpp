////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Gcode Processor Library
//
// Tools for parsing gcode and calculating printer state from parsed gcode commands.
//
// Copyright(C) 2020 - Brad Hochgesang
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "parsed_command_parameter.h"
#include "parsed_command.h"
parsed_command_parameter::parsed_command_parameter()
{
	value_type = 'N';
	name.reserve(1);
}

parsed_command_parameter::parsed_command_parameter(const std::string name, double value) : name(name), double_value(value)
{
	value_type = 'F';
}

parsed_command_parameter::parsed_command_parameter(const std::string name, const std::string value) : name(name), string_value(value)
{
	value_type = 'S';
}

parsed_command_parameter::parsed_command_parameter(const std::string name, const unsigned long value) : name(name), unsigned_long_value(value)
{
	value_type = 'U';
}
parsed_command_parameter::~parsed_command_parameter()
{

}
