#include "light.h"

bool light::in_shadow(const ray& r, const shadeRec& sr)
{
	return false;
}

double light::pdf(shadeRec& sr) const
{
	return 1.0;
}
double light::G(shadeRec& sr) const
{
	return 1.0;
}

void light::set_shadows_light(bool arg_shadows)
{
	shadows = arg_shadows;
}
