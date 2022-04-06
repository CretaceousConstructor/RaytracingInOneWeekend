#include "reflective.h"

void reflective::set_reflective_k(double arg_kr)
{
	if (reflective_brdf != nullptr) {
		reflective_brdf->kr = arg_kr;
	}
}

void reflective::set_reflective_color(TrekMath::color arg_cr)
{
	if (reflective_brdf != nullptr) {
		reflective_brdf->cr = arg_cr;
	}
}

TrekMath::color reflective::shade(shadeRec& sr)
{
   TrekMath::color L = phong::shade(sr);//直接光照
   
   TrekMath::vec3 wo = -sr.cast_ray.direction();

   TrekMath::vec3 wi;

   TrekMath::color fr = reflective_brdf->sample_f(sr,wi,wo);

   ray reflected_ray(sr.hitPoint,wi);

   L += fr * sr.wor->tracer_ptr->trace_ray(reflected_ray,sr.depth +1) * glm::dot(sr.normal,wi);

   return L;


}

TrekMath::color reflective::area_light_shade(shadeRec& sr)
{
	TrekMath::color L = phong::area_light_shade(sr);//直接光照

	TrekMath::vec3 wo = -sr.cast_ray.direction();

	TrekMath::vec3 wi;

	TrekMath::color fr = reflective_brdf->sample_f(sr, wi, wo);

	ray reflected_ray(sr.hitPoint, wi);

	L += fr * sr.wor->tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * glm::dot(sr.normal, wi);

	return L;
}

TrekMath::color reflective::path_shade(shadeRec& sr)
{
	TrekMath::vec3 wo  = -sr.cast_ray.direction();
	TrekMath::vec3 wi;
	double pdf;
	color fr = reflective_brdf->sample_f(sr,wi,wo,pdf);
	ray reflected_ray(sr.hitPoint,wi);
	return (fr *sr.wor->tracer_ptr->trace_ray(reflected_ray,sr.depth+1)  * glm::dot(sr.normal,wi) / pdf);





}

TrekMath::color reflective::global_shade(shadeRec& sr)
{

	TrekMath::vec3 wo = -sr.cast_ray.direction();
	TrekMath::vec3 wi;
	double pdf;
	color fr = reflective_brdf->sample_f(sr, wi, wo, pdf);
	ray reflected_ray(sr.hitPoint, wi);
	double NdotWi = glm::dot(sr.normal, wi);

	if (sr.depth == 0) {
		return fr* sr.wor->tracer_ptr->trace_ray(reflected_ray, sr.depth + 2)* NdotWi / pdf;
	}
	
	else
	{
		return fr* sr.wor->tracer_ptr->trace_ray(reflected_ray, sr.depth + 1)* NdotWi / pdf;

	}

}
