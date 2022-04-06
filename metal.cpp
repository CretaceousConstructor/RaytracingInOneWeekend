#include "metal.h"

metal::metal(const color &a, double f) :
    material(),
    albedo(a),
    fuzz(f < 1. ? f : 1.)
{
}

TrekMath::color metal::path_shade(shadeRec &sr)
{
	vec3 reflected   = reflect(glm::normalize(sr.cast_ray.direction()), sr.normal);
	auto scattered   = ray(sr.hitPoint, reflected + fuzz*random_in_unit_sphere(),sr.cast_ray.time());
	auto attenuation = albedo;
	


	if (glm::dot(scattered.direction(), sr.normal) > 0)        //ray will scatter
	{
		return attenuation * sr.wor->tracer_ptr->trace_ray(scattered, sr.depth + 1);
	}
	else        //ray will not scatter
	{
		return color(0., 0., 0.);
	}



}
