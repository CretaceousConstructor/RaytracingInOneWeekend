#include "perfectTransmitter.h"

color perfectTransmitter::sample_f(const shadeRec& sr, const vec3& wo, vec3& wt) const
{
    TrekMath::normal n (sr.normal);
    double cos_theta_i = glm::dot(n,wo);
    double eta = ior;
    if (cos_theta_i < 0.)
    {
        cos_theta_i = -cos_theta_i;
        n = -n;
        eta = 1.0 / eta;
    }

    double temp = 1.0 - (1.0 - cos_theta_i * cos_theta_i) / (eta * eta);
    double cos_theta2 = glm::sqrt(temp);
    wt = -wo / eta  - (cos_theta2 - cos_theta_i / eta) * n;
    return (kt / (eta * eta) * TrekMath::color(1.,1.,1.) / fabs(glm::dot(sr.normal,wt)));
}

bool perfectTransmitter::tir(const shadeRec& sr) const
{
    TrekMath::vec3 wo(-sr.cast_ray.direction());
    double cos_thetai = glm::dot(sr.normal,wo);
    double eta = ior;
    if (cos_thetai < 0.) {
        eta = 1. / eta;
    }


    return (1. - (1. - cos_thetai * cos_thetai) / (eta * eta) < 0.0);
}
