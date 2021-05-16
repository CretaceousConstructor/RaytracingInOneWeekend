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
	throw "shit your pants";
	return TrekMath::color();
}

void emissive::setRadianceScaling(double arg_ls)
{
	ls = arg_ls;
}

void emissive::setEmissiveColor(TrekMath::color c)
{
	ce = c;
}
