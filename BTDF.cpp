#include "BTDF.h"

TrekMath::color BTDF::f(const shadeRec &hit_rec, const TrekMath::vec3 &wi, const TrekMath::vec3 &wo) const
{
	return {};
}

TrekMath::color BTDF::sample_f(const shadeRec &sr, const TrekMath::vec3 &wo, TrekMath::vec3 &wt) const
{
	return {};
}

TrekMath::color BTDF::sample_f(const shadeRec &sr, const TrekMath::vec3 &wo, TrekMath::vec3 &wt, double &pdf) const
{
	return {};
}

TrekMath::color BTDF::rho(const shadeRec &sr, const TrekMath::vec3 &wo) const
{
	return {};
}

bool BTDF::tir(const shadeRec &shade_rec) const
{
	return false;
}
