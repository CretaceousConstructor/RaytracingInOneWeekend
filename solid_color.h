#pragma once

#include "texture.h"

class solid_color : public texture
{
  public:
	solid_color() = default;
	solid_color(color c);

	solid_color(double red, double green, double blue);

	virtual color value(const texcoor2d &txcor, const vec3 &p) const override;

  private:
	color color_value;
};
