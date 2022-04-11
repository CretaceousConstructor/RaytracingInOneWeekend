#pragma once

#include "texture.h"
#include <iostream>
#include "imageLoader.h"

class image_texture : public texture
{
  public:
	constexpr static int bytes_per_pixel = 3;

	image_texture();

	image_texture(const char *filename);

	~image_texture();

	virtual color value(const TrekMath::texcoor2d &txcor, const point3 &p) const override;

  private:
	unsigned char *data;
	int            width, height;
	int            bytes_per_scanline;




};
