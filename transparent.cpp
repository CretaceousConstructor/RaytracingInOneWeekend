#include "transparent.h"

transparent::transparent()
    :
    phong(),
    reflective_brdf(std::make_unique<perfectSpecular>()),
    specular_btdf(std::make_unique<perfectTransmitter>())

{
}

TrekMath::color transparent::shade(shadeRec& sr)
{
    TrekMath::color L(phong::shade(sr));

    TrekMath::vec3 wo = -sr.cast_ray.direction();

    TrekMath::vec3 wi;

    TrekMath::color fr = reflective_brdf->sample_f(sr,wi,wo);
    ray reflected_ray(sr.hitPoint,wi);

    if (specular_btdf->tir(sr))
    {
        L += sr.wor->tracer_ptr->trace_ray(reflected_ray,sr.depth + 1);
        //kr = 1.0
    }

    else {

        TrekMath::vec3 wt;
        color ft = specular_btdf->sample_f(sr,wo,wt);
        ray transmitted_ray(sr.hitPoint,wt);
        L += fr * sr.wor->tracer_ptr->trace_ray(reflected_ray,sr.depth+1)*fabs(glm::dot(sr.normal,wi));
        L += ft * sr.wor->tracer_ptr->trace_ray(reflected_ray,sr.depth+1)*fabs(glm::dot(sr.normal,wt));
    }

    return L;
}

void transparent::set_transmitter_ior(double arg_ior)
{
    if (specular_btdf != nullptr) {
        specular_btdf->ior = arg_ior;
    }
}

void transparent::set_transmitter_k(double arg_kt)
{
    if (specular_btdf != nullptr) {
        specular_btdf->kt = arg_kt;
    }
}
void transparent::set_reflective_k(double arg_kr)
{
    if (reflective_brdf != nullptr) {
        reflective_brdf->kr = arg_kr;
    }
}

void transparent::set_reflective_color(TrekMath::color arg_cr)
{
    if (reflective_brdf != nullptr) {
        reflective_brdf->cr = arg_cr;
    }
}
