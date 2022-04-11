#include "noise_texture.h"

noise_texture::noise_texture(double sc) :
    scale(sc)
{}

color noise_texture::value(const TrekMath::texcoor2d &txcor, const point3 &p) const
{
	return color(1, 1, 1) * 0.5 * (1 + sin(scale * p.z + 10 * noise.turb(p)));
}
