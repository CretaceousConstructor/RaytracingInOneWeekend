#include "diffuse_light.h"

diffuse_light::diffuse_light(shared_ptr<texture> a) :
    emit(a)
{}

diffuse_light::diffuse_light(color c) :
    emit(make_shared<solid_color>(c))
{}

TrekMath::color diffuse_light::path_shade(shadeRec &sr)
{
	if (sr.front_face)
	{
		const color emitted = emit->value(sr.texcor, sr.hitPoint);
		return emitted;
	}

	return {0., 0., 0.};
}

TrekMath::color diffuse_light::path_shade(shadeRec &sr, const hittable &lights)
{
	if (sr.front_face)
	{
		const color emitted = emit->value(sr.texcor, sr.hitPoint);
		return emitted;
	}

	return {0., 0., 0.};
}

TrekMath::color diffuse_light::path_shade(shadeRec &sr, const hittable &objects, std::shared_ptr<hittable> lights)
{
	if (sr.front_face)
	{
		const color emitted = emit->value(sr.texcor, sr.hitPoint);
		return emitted;
	}

	return {0., 0., 0.};
}
