#include "diffuse.h"

diffuse::diffuse(const color &a ) :
    material(),
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

	auto scattered = ray(sr.hitPoint, scatter_direction,sr.cast_ray.time());
	auto attenuation = albedo;

	return attenuation * sr.wor->tracer_ptr->trace_ray(scattered, sr.depth + 1);





}
