
#include "image_texture.h"

image_texture::image_texture() :
    data(nullptr), width(0), height(0), bytes_per_scanline(0)
{
}

image_texture::image_texture(const char *filename)
{
	auto components_per_pixel = bytes_per_pixel;

	data = stbi_load(
	    filename, &width, &height, &components_per_pixel, components_per_pixel);

	if (!data)
	{
		std::cerr << "ERROR: Could not load texture image file '" << filename << "'.\n";
		width = height = 0;
	}

	bytes_per_scanline = bytes_per_pixel * width;
}

image_texture::~image_texture()
{
	delete data;
}

color image_texture::value(const TrekMath::texcoor2d &txcor, const point3 &p) const
{
	// If we have no texture data, then return solid cyan as a debugging aid.
	if (data == nullptr)
	{
		return color(0, 1, 1);
	}

	// Clamp input texture coordinates to [0,1] x [1,0]
	auto u = clamp(txcor.u, 0.0, 1.0);
	auto v = 1.0 - clamp(txcor.v, 0.0, 1.0);        // Flip V to image coordinates

	auto i = static_cast<int>(u * width);
	auto j = static_cast<int>(v * height);

	// Clamp integer mapping, since actual coordinates should be less than 1.0
	if (i >= width)
	{
		i = width - 1;
	}
	if (j >= height)
	{
		j = height - 1;
	}

	const auto color_scale = 1.0 / 255.0;
	auto       pixel       = data + j * bytes_per_scanline + i * bytes_per_pixel;

	return color(color_scale * pixel[0], color_scale * pixel[1], color_scale * pixel[2]);
}
