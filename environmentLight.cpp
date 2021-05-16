#include "environmentLight.h"

void environmentLight::set_sampler(std::unique_ptr<sampler>&& arg_sampler_ptr)
{

	sampler_ptr = std::move(arg_sampler_ptr);
}

void environmentLight::set_material(std::shared_ptr<material>&& arg_material_ptr)
{
	material_ptr = arg_material_ptr;
}

TrekMath::vec3 environmentLight::get_direction(shadeRec& sr)
{


	w = sr.normal;
	v = glm::cross(TrekMath::vec3(0.0034, 1, 0.0071), w);
	v = glm::normalize(v);
	u = glm::cross(v, w);

	TrekMath::point3 sp = sampler_ptr->sample_hemisphere();

	wi = sp.x * u + sp.y * v + sp.z * w;

	return (wi);


}

TrekMath::color environmentLight::L(shadeRec& sr)
{
	return (material_ptr->get_emissive_Le(sr));
}

bool environmentLight::in_shadow(const ray& r, const shadeRec& sr)
{
	
	double t;
	for (auto obj : sr.wor->objects) {
		if (obj->shadow_hit(r, t)) {
			return true;
		}
	}

	return false;

}

double environmentLight::pdf( shadeRec& sr) const
{
	double cosTheta = glm::dot(sr.normal, wi) / glm::pi<double>();//²ÎÊýpi;

	return cosTheta;
}
