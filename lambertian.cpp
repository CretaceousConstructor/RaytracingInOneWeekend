#include "Lambertian.h"

color lambertian::f(const shadeRec& hit_rec, const vec3& wi, const vec3& wo) const

{ 
    
    //������˵��Ӧ�ú�λ���й�?
    return ( (1.0 / glm::pi<double>()) * kd * cd );   //f = ��/��
}

color lambertian::sample_f(const shadeRec& hit_rec, vec3& wi, const vec3& wo) const
{
    return color();
}

color lambertian::rho(const shadeRec& hit_rec, const vec3& wo) const
{
    return kd * cd;
}

