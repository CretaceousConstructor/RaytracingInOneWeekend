#include "solid_color.h"

solid_color::solid_color(color c) :
    color_value(c)
{}

solid_color::solid_color(double red, double green, double blue) :
    solid_color(color(red, green, blue))
{}

color solid_color::value(const texcoor2d &txcor, const vec3 &p) const
{
	return color_value;
}
