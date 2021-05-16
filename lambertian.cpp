#include "Lambertian.h"

color lambertian::f(const shadeRec& hit_rec, const vec3& wi, const vec3& wo) const

{ 
    
    //按理来说，应该和位置有关?
    return ( (1.0 / glm::pi<double>()) * kd * cd );   //f = ρ/π
}

color lambertian::sample_f(const shadeRec& hit_rec, vec3& wi, const vec3& wo) const
{
    return color();
}

color lambertian::rho(const shadeRec& hit_rec, const vec3& wo) const
{
    return kd * cd;
}

