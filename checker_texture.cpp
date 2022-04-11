#include "checker_texture.h"

checker_texture::checker_texture(shared_ptr<texture> _even, shared_ptr<texture> _odd) :
    even(_even), odd(_odd)
{}

checker_texture::checker_texture(color c1, color c2) :
    even(make_shared<solid_color>(c1)), odd(make_shared<solid_color>(c2))
{}

color checker_texture::value(const texcoor2d &txcor, const point3 &p) const
{
	auto sines = sin(10 * p.x) * sin(10 * p.y) * sin(10 * p.z);
	if (sines < 0)
		return odd->value(txcor, p);
	else
		return even->value(txcor, p);
}
