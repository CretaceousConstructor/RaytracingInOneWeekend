#include "BTDF.h"

color BTDF::f(const shadeRec& hit_rec, const vec3& wi, const vec3& wo) const
{
    return color();
}

color BTDF::sample_f(const shadeRec& sr, const vec3& wo, vec3& wt) const
{
    return color();
}

color BTDF::sample_f(const shadeRec& sr, const vec3& wo, vec3& wt, double& pdf) const
{
    return color();
}



color BTDF::rho(const shadeRec& sr, const vec3& wo) const
{
    return color();
}



bool BTDF::tir(const shadeRec& shade_rec) const
{
    return false;
}
