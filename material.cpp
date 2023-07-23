#include "material.h"

TrekMath::color material::shade(shadeRec &sr)
{
	return {};
}

TrekMath::color material::area_light_shade(shadeRec &sr)
{
	return {};
}

TrekMath::color material::get_emissive_Le(shadeRec &sr)
{
	return {};
}

TrekMath::color material::path_shade(shadeRec &sr, const hittable &objects, std::shared_ptr<hittable> lights)
{
	return {

	};
}



color material::whitted_shade(shadeRec &sr)
{
	return {};
}

color material::path_shade(shadeRec &sr)
{
	return {};
}

TrekMath::color material::path_shade(shadeRec &sr, const hittable &lights)
{
	return {};
}

double material::scattering_pdf(const shadeRec &sr, const ray &scattered)
{
	return 0.0;
}

TrekMath::color material::global_shade(shadeRec &sr)
{
	return {};
}
