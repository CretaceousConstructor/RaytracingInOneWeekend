#include "perfectSpecular.h"

color perfectSpecular::f(const shadeRec& hit_rec, const vec3& wi, const vec3& wo) const
{
	return color();
}

color perfectSpecular::sample_f(const shadeRec& sr, vec3& wi, const vec3& wo) const
{
   double NdotWo = glm::dot(sr.normal , wo);

   wi = -wo + 2.0 * sr.normal * NdotWo;
   
   return (kr * cr / glm::dot(sr.normal, wi));
}

color perfectSpecular::sample_f(const shadeRec& sr, vec3& wi, const vec3& wo, double& pdf) const
{
	double NdotWo = glm::dot(sr.normal, wo);

	wi = -wo + 2.0 * sr.normal * NdotWo;
	pdf = glm::dot(sr.normal,wi);

	return (kr * cr);
}

color perfectSpecular::rho(const shadeRec& sr, const vec3& wo) const
{
	return color();
}


