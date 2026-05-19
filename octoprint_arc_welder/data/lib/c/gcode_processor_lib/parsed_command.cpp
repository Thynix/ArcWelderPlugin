////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Gcode Processor Library
//
// Tools for parsing gcode and calculating printer state from parsed gcode commands.
//
// Copyright(C) 2020 - Brad Hochgesang
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "parsed_command.h"
#include <sstream>
#include <iomanip>
#include <stdlib.h>
parsed_command::parsed_command()
{

	command.reserve(8);
	gcode.reserve(128);
	comment.reserve(128);
	parameters.reserve(6);
	is_known_command = false;
	is_empty = true;
}

void parsed_command::clear()
{

	command.clear();
	gcode.clear();
	comment.clear();
	parameters.clear();
	is_known_command = false;
	is_empty = true;
}

std::string parsed_command::rewrite_gcode_string()
{
	std::stringstream stream;

	// add command
	stream << command;
	if (parameters.size() > 0)
	{
		for (unsigned int index = 0; index < parameters.size(); index++)
		{
			parsed_command_parameter p = parameters[index];

			if (p.name == "E")
			{
				stream << std::fixed << std::setprecision(5);
			}
			else if (p.name == "F")
			{
				stream << std::fixed << std::setprecision(0);
			}
			else
			{
				stream << std::fixed << std::setprecision(3);
			}

			stream << " " << p.name;
			switch (p.value_type)
			{
			case 'S':
				stream << p.string_value;
				break;
			case 'F':
				stream << p.double_value;
				break;
			case 'U':
				stream << p.unsigned_long_value;
				break;
			}
		}
	}
	if (comment.size() > 0)
	{
		stream << ";" << comment;
	}
	return stream.str();
}

std::string parsed_command::to_string()
{
	if (comment.size() > 0)
	{
		return gcode + ";" + comment;
	}
	return gcode;
}
