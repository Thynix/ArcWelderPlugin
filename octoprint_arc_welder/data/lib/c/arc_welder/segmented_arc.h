////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Arc Welder: Anti-Stutter Library
//
// Compresses many G0/G1 commands into G2/G3(arc) commands where possible, ensuring the tool paths stay within the specified resolution.
// This reduces file size and the number of gcodes per second.
//
// Uses the 'Gcode Processor Library' for gcode parsing, position processing, logging, and other various functionality.
//
// Copyright(C) 2020 - Brad Hochgesang
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "segmented_shape.h"
#include <iomanip>
#include <sstream>

#define GCODE_CHAR_BUFFER_SIZE 100
#define DEFAULT_MAX_RADIUS_MM 1000000.0 // 1km
class segmented_arc :
	public segmented_shape
{
public:
	segmented_arc();
	segmented_arc(int min_segments = DEFAULT_MIN_SEGMENTS, int max_segments = DEFAULT_MAX_SEGMENTS, double resolution_mm = DEFAULT_RESOLUTION_MM, double max_radius_mm = DEFAULT_MAX_RADIUS_MM);
	virtual ~segmented_arc();
	virtual bool try_add_point(point p, double e_relative);
	std::string get_shape_gcode_absolute(double e, double f);
	std::string get_shape_gcode_relative(double f);

	virtual bool is_shape() const;
	point pop_front(double e_relative);
	point pop_back(double e_relative);
	bool try_get_arc(arc & target_arc);
	double get_max_radius() const;
	// static gcode buffer

private:
	bool try_add_point_internal_(point p, double pd);
	bool does_circle_fit_points_(circle& c) const;
	bool try_get_arc_(const circle& c, arc& target_arc);
	std::string get_shape_gcode_(bool has_e, double e, double f) const;
	circle arc_circle_;
	double max_radius_mm_;
};
