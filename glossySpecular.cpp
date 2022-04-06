#include "glossySpecular.h"

color glossySpecular::f(const shadeRec &sr, const vec3 &wi, const vec3 &wo) const
{
	TrekMath::color L(0., 0., 0.);

	double NdotWi = glm::dot(sr.normal, wi);

	TrekMath::vec3 r(-wi + 2.0 * sr.normal * NdotWi);

	double RdotWo = glm::dot(r, wo);
	if (RdotWo > 0.)
	{
		L = cs * ks * glm::pow(RdotWo, exp);
	}
	return L;
}

color glossySpecular::sample_f(const shadeRec &sr, vec3 &wi, const vec3 &wo, double &pdf) const
{
	double         NdotWo = glm::dot(sr.normal, wo);
	TrekMath::vec3 r      = -wo + 2.0 * NdotWo * sr.normal;        //direction of mirror reflection

	TrekMath::vec3 w = r;
	TrekMath::vec3 u = glm::cross(TrekMath::vec3(0.00424, 1., 0.00764), w);
	u                = glm::normalize(u);
	TrekMath::vec3 v = glm::cross(u, w);

	TrekMath::point3 sp = sam->sample_hemisphere();

	wi = sp.x * u + sp.y * v + sp.z * w;        //∑¥…‰π‚œﬂ

	if (glm::dot(sr.normal, wi) < 0.)
	{
		wi = -sp.x * u - sp.y * v + sp.z * w;
	}

	double phong_lobe = glm::pow(glm::dot(r, wi), exp);
	pdf               = phong_lobe * glm::dot(sr.normal, wi);
	return (ks * cs * phong_lobe);
}

color glossySpecular::rho(const shadeRec &sr, const vec3 &wo) const
{
	return TrekMath::color();
}

color glossySpecular::sample_f(const shadeRec &sr, vec3 &wi, const vec3 &wo) const
{
	return color();
}

void glossySpecular::set_samples(const int num_samples, const int num_sets, const double exp)
{
	sam = std::make_unique<multiJittering>(num_samples, num_sets, exp);
}
