#include "Lambertian.h"

lambertian::lambertian(std::unique_ptr<sampler> &&arg_sam)
		:
		BRDF(std::move(arg_sam))
	{
	}
color lambertian::f(const shadeRec &hit_rec, const vec3 &wi, const vec3 &wo) const

{

	//按理来说，应该和位置有关?
	return ((1.0 / glm::pi<double>()) * kd * cl);   //f = ρ/π
}

color lambertian::sample_f(const shadeRec& sr, vec3& wi, const vec3& wo, double& pdf) const
{

	TrekMath::vec3 w = sr.normal;
	TrekMath::vec3 v = glm::cross(TrekMath::vec3(0.0034, 1., 0.0071), w);

	v = glm::normalize(v);
	TrekMath::vec3 u = glm::cross(v, w);

	TrekMath::point3 sp = sam->sample_hemisphere();
	wi = sp.x * u + sp.y * v + sp.z * w;
	wi = glm::normalize(wi);

	pdf = glm::dot(sr.normal,wi) * (1. / glm::pi<double>());

	return (kd * cl * (1. / glm::pi<double>() ));

}

color lambertian::rho(const shadeRec& sr, const vec3& wo) const
{
	return kd * cl;
}

