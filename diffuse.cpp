#include "diffuse.h"

diffuse::diffuse(const color &a) :
    albedo(std::make_shared<solid_color>(a))
{
}

diffuse::diffuse(std::shared_ptr<texture> a) :
    albedo(a)
{
}

TrekMath::color diffuse::path_shade(shadeRec &sr)
{
	auto scatter_direction = sr.normal + random_unit_vector();

	// Catch degenerate scatter direction
	if (near_zero(scatter_direction))
	{
		scatter_direction = sr.normal;
	}

	auto scattered   = ray(sr.hitPoint, scatter_direction, sr.cast_ray.time());
	auto attenuation = albedo->value(sr.texcor, sr.hitPoint);

	return attenuation * (sr.wor->tracer_ptr->trace_ray(scattered, sr.depth + 1));
}
