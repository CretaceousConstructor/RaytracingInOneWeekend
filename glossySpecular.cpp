#include "glossySpecular.h"

color glossySpecular::f(const shadeRec& sr, const vec3& wi, const vec3& wo) const
{
    TrekMath::color L(0.,0.,0.);

    double ndotWi= glm::dot(sr.normal ,wi);


    TrekMath::vec3 r(-wi + 2.0 * sr.normal * ndotWi);

    auto len = glm::length(r);

    double RdotWo = glm::dot(r,wo);
    if (RdotWo > 0.) {

        L = ks * glm::pow(RdotWo,exp);

    }
        

    return L;
}
