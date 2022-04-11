#pragma once
#include "perlin.h"
#include "texture.h"

class noise_texture : public texture
{
  public:
	noise_texture() = default;
	noise_texture(double sc);

	color value(const TrekMath::texcoor2d &txcor, const point3 &p) const override;

  private:
	perlin noise;
	double scale;
};
