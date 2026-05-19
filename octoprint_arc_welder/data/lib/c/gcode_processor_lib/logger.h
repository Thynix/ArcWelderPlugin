////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Gcode Processor Library
//
// Tools for parsing gcode and calculating printer state from parsed gcode commands.
//
// Copyright(C) 2020 - Brad Hochgesang
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <cstdarg>
#include <stdio.h>
#include <ctime>
//#include <chrono>
#include <array>

#define LOG_LEVEL_COUNT 7
#define CLOCKS_PER_MS (CLOCKS_PER_SEC / 1000.0)
enum log_levels { NOSET, VERBOSE, DEBUG, INFO, WARNING , ERROR, CRITICAL};
//const std::array<std::string, 7> log_level_names = { {"NOSET", "VERBOSE", "DEBUG", "INFO", "WARNING", "ERROR", "CRITICAL"} };
static const int log_level_names_size = 7;
static const char* log_level_names[] = {"NOSET", "VERBOSE", "DEBUG", "INFO", "WARNING", "ERROR", "CRITICAL"};
const static int log_level_values[LOG_LEVEL_COUNT] = { 0, 5, 10,  20,  30,  40,  50};

class logger
{
public:
	logger(std::vector<std::string> names, std::vector<int> levels);
	virtual ~logger();

	void set_log_level_by_value(const int logger_type, const int log_level_value);
	void set_log_level_by_value(const int log_level_value);

	void set_log_level(const int logger_type, const int log_level);
	void set_log_level(const int log_level);

	virtual void log(const int logger_type, const int log_level, const std::string& message);
	virtual void log(const int logger_type, const int log_level, const std::string& message, bool is_exception);
	virtual void log_exception(const int logger_type, const std::string& message);
	static int get_log_level_value(const int log_level);
	static int get_log_level_for_value(int log_level_value);
	virtual bool is_log_level_enabled(const int logger_type, const int log_level);
protected:
	virtual void create_log_message(const int logger_type, const int log_level, const std::string& message, std::string& output);

	bool loggers_created_;
private:
	std::string* logger_names_;
	int * logger_levels_;
	int num_loggers_;
	static void get_timestamp(std::string &timestamp);

};
