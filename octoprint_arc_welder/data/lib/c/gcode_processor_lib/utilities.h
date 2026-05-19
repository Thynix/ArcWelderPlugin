////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Gcode Processor Library
//
// Tools for parsing gcode and calculating printer state from parsed gcode commands.
//
// Copyright(C) 2020 - Brad Hochgesang
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>
#include <vector>
#include <set>
class utilities{
public:
	static bool is_zero(double x);
	static int round_up_to_int(double x);
	static bool is_equal(double x, double y);
	static bool greater_than(double x, double y);
	static bool greater_than_or_equal(double x, double y);
	static bool less_than(double x, double y);
	static bool less_than_or_equal(double x, double y);

	// custom tolerance functions
	static bool is_zero(double x, double tolerance);
	static bool is_equal(double x, double y, double tolerance);
	static int round_up_to_int(double x, double tolerance);
	static bool greater_than(double x, double y, double tolerance);
	static bool greater_than_or_equal(double x, double y, double tolerance);
	static bool less_than(double x, double y, double tolerance);
	static bool less_than_or_equal(double x, double y, double tolerance);

	static double get_cartesian_distance(double x1, double y1, double x2, double y2);
	static double get_cartesian_distance(double x1, double y1, double z1, double x2, double y2, double z2);
	static std::string to_string(double value);
	static std::string to_string(int value);
	static char* to_string(double value, unsigned short precision, char* str);
	static std::string ltrim(const std::string& s);
	static std::string rtrim(const std::string& s);
	static std::string trim(const std::string& s);
	static std::istream& safe_get_line(std::istream& is, std::string& t);
	static std::string center(std::string input, int width);
	static std::string get_percent_change_string(int v1, int v2, int precision);

	static int get_num_digits(int x);
	static int get_num_digits(double x);

	static std::vector<std::string> splitpath(const std::string& str);
	static bool get_file_path(const std::string& file_path, std::string& path);
	static bool get_temp_file_path_for_file(const std::string& file_path, std::string& temp_file_path);
	static std::string create_uuid();


protected:
	static const std::string WHITESPACE_;
	static const char PATH_SEPARATOR_ =
#ifdef _WIN32
		'\\';
#else
		'/';
#endif
	static const char GUID_RANGE[];
	static const bool GUID_DASHES[];
private:
	utilities();

};
