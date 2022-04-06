#include "BRDF.h"

color BRDF::f(const shadeRec& hit_rec, const vec3& wi, const vec3& wo) const
{
	return color();
}

color BRDF::sample_f(const shadeRec& hit_rec, vec3& wi, const vec3& wo) const
{
	return color();
}

color BRDF::rho(const shadeRec& hit_rec, const vec3& wo) const
{
	return color();
}

color BRDF::sample_f(const shadeRec& hit_rec, vec3& wi, const vec3& wo, double& pdf) const
{
	return color();
}


void BRDF::set_samples(std::unique_ptr<sampler>&& arg_sam)
{
	sam = std::move(arg_sam);
}
