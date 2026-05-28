////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Gcode Processor Library
//
// Tools for parsing gcode and calculating printer state from parsed gcode commands.
//
// Copyright(C) 2020 - Brad Hochgesang
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GCODE_PARSER_H
#define GCODE_PARSER_H
#include <string>
#include <vector>
#include <set>
#include "parsed_command.h"
#include "parsed_command_parameter.h"
static const std::string GCODE_WORDS = "GMT";

class gcode_parser
{
public:
	gcode_parser();
	~gcode_parser();
	bool try_parse_gcode(const char * gcode, parsed_command & command);
	bool try_parse_gcode(const char* gcode, parsed_command& command, bool preserve_format);
	parsed_command parse_gcode(const char * gcode);
	parsed_command parse_gcode(const char* gcode, bool preserve_format);
private:
	gcode_parser(const gcode_parser &source);
	// Variables and lookups
	std::set<std::string> text_only_functions_;
	std::set<std::string> parsable_commands_;
	// Functions
	bool try_extract_double(char ** p_p_gcode, double * p_double) const;
	static bool try_extract_gcode_command(char ** p_p_gcode, std::string * p_command);
	static bool try_extract_text_parameter(char ** p_p_gcode, std::string * p_parameter);
	bool try_extract_parameter(char ** p_p_gcode, parsed_command_parameter * parameter) const;
	static bool try_extract_t_parameter(char ** p_p_gcode, parsed_command_parameter * parameter);
	static bool try_extract_unsigned_long(char ** p_p_gcode, unsigned long * p_value);
	double static ten_pow(unsigned short n);
	bool try_extract_comment(char ** p_p_gcode, std::string * p_comment);
	static bool try_extract_at_command(char ** p_p_gcode, std::string * p_command);
	bool try_extract_octolapse_parameter(char ** p_p_gcode, parsed_command_parameter * p_parameter);
};
#endif
