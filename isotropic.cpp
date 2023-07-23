#include "isotropic.h"

isotropic::isotropic(color c) :
    albedo(make_shared<solid_color>(c))
{}

isotropic::isotropic(shared_ptr<texture> a) :
    albedo(a)
{}

TrekMath::color isotropic::path_shade(shadeRec &sr)
{

	ray scattered = ray(sr.hitPoint, random_within_unit_sphere(), sr.cast_ray.time());
	auto attenuation = albedo->value(sr.texcor, sr.hitPoint);
	return attenuation * (sr.wor->tracer_ptr->trace_ray(scattered, sr.depth + 1));



}
