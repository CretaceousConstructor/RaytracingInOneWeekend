#include "emissive.h"

TrekMath::color emissive::get_emissive_Le(shadeRec& sr)
{
	return ls * ce;
}

TrekMath::color emissive::area_light_shade(shadeRec& sr)
{
	if (glm::dot(-sr.normal, sr.cast_ray.direction()) > 0.0) {

		return ls * ce;
	}
	else {
		return TrekMath::color(0., 0., 0.);
	}
}

TrekMath::color emissive::shade(shadeRec& sr)
{
	if (glm::dot(-sr.normal, sr.cast_ray.direction()) > 0.0) {
		return ls * ce;
	}
	else {
		return TrekMath::color(0., 0., 0.);
	}
}

TrekMath::color emissive::path_shade(shadeRec& sr)
{


	if (glm::dot(-sr.normal, sr.cast_ray.direction()) > 0.0) {
		return ls * ce;
	}
	else {
		return TrekMath::color(0., 0., 0.);
	}

}

TrekMath::color emissive::global_shade(shadeRec& sr)
{
	if (sr.depth == 1) {
		return color(0., 0., 0.);
	}
	if (glm::dot(-sr.normal, sr.cast_ray.direction()) > 0.)
	{
		return (ls * ce);
	}
	else {
		return TrekMath::color(0., 0., 0.);
	}

}



void emissive::setRadianceScaling(double arg_ls)
{
	ls = arg_ls;
}

void emissive::setEmissiveColor(TrekMath::color c)
{


	ce = c;
}
