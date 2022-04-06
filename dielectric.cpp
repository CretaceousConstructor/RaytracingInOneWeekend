#include "dielectric.h"

TrekMath::color dielectric::path_shade(shadeRec &sr)
{
	auto   attenuation      = color(1.0, 1.0, 1.0);
	double refraction_ratio = sr.front_face ? (1.0 / ir) : ir;        //区分冲空气进入介质，还是从介质进入空气

	vec3   unit_direction = glm::normalize(sr.cast_ray.direction());
	double cos_theta      = fmin(glm::dot(-unit_direction, sr.normal), 1.0);
	double sin_theta      = sqrt(1.0 - cos_theta * cos_theta);

	bool cannot_refract = refraction_ratio * sin_theta > 1.0;
	vec3 direction;

	if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double()) //全反射或者schlick给出反射概率更大，则发射反射光线，不发射折射光线
		direction = reflect(unit_direction, sr.normal);
	else
		direction = refract(unit_direction, sr.normal, refraction_ratio);

	auto scattered = ray(sr.hitPoint, direction,sr.cast_ray.time()); 
	
	return attenuation * sr.wor->tracer_ptr->trace_ray(scattered, sr.depth + 1);
}

double dielectric::reflectance(double cosine, double ref_idx)
{
	// Use Schlick's approximation for reflectance.
	auto r0 = (1 - ref_idx) / (1 + ref_idx);
	r0      = r0 * r0;
	return r0 + (1 - r0) * pow((1 - cosine), 5);
}
