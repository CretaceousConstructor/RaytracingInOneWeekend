#include "noise_texture.h"

noise_texture::noise_texture(float sc) :
    scale(sc)
{}

color noise_texture::value(const TrekMath::texcoor2d &txcor, const point3 &p) const
{
	return vec3(1, 1, 1) * 0.5 * (1 + sin(scale * p.x) + 5 * noise.noise(p));
}
