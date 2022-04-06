#include "glossyReflector.h"

glossyReflector::glossyReflector() :
    phong(),
    glossy_specular_brdf(std::make_unique<glossySpecular>())
{
}

void glossyReflector::set_sampler(const int num_samples, const int sample_sets, const double exp)
{
    glossy_specular_brdf->set_samples(num_samples, sample_sets, exp);
}

void glossyReflector::set_k_glossy_reflective(const double k)
{
    if (glossy_specular_brdf != nullptr)
    {
        glossy_specular_brdf->ks = k;
    }
}

void glossyReflector::set_exponent_glossy_reflective(const double exp)
{
    if (glossy_specular_brdf != nullptr)
    {
        glossy_specular_brdf->exp = exp;
        /*auto num_samples = glossy_specular_brdf->sam->get_num_of_samples_per();
        auto sample_sets = glossy_specular_brdf->sam->get_num_of_sets();
        glossy_specular_brdf->set_samples(num_samples, sample_sets, exp);*/
    }
}

void glossyReflector::set_color_glossy_reflective(TrekMath::color cr)
{
    if (glossy_specular_brdf != nullptr)
    {
        glossy_specular_brdf->cs = cr;
    }
}

TrekMath::color glossyReflector::area_light_shade(shadeRec &sr)
{
    TrekMath::color L(phong::area_light_shade(sr));
    TrekMath::vec3  wo(-sr.cast_ray.direction());
    TrekMath::vec3  wi;
    double          pdf;

    TrekMath::color fr(glossy_specular_brdf->sample_f(sr, wi, wo, pdf));

    ray reflected_ray(sr.hitPoint, wi);
    L += fr * sr.wor->tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * glm::dot(sr.normal, wi) / pdf;
    return L;

    //auto dd = glm::dot(sr.normal, wi);
    //auto lenshit = glm::length(sr.normal);
    //auto lenshit2 = glm::length(wi);
    //if (glm::abs(sr.hitPoint.x - (-44.835588353)) < 0.00000001) {
    //	int ab = 32;
    //}
    /*if (dd < 0.) {
        int a = 32;
    }
    if (glm::length(fr) < 0.001) {
        int b = 44;
    }
    if (fr.r < 0. || fr.g < 0. || fr.b < 0.) {
        int c = 55;
    }
    if (pdf < 0.) {
        int g = 65;
    }

    if (glm::length(L) < 0.001) {
        int b = 44;
    }
    if (fr.r < 0. || fr.g < 0. || fr.b < 0.) {
        int c = 55;
    }
    auto shit2 = glm::dot(sr.normal, wi);
    if (shit2 < 0.) {
        int ra = 434;
    }*/
}

TrekMath::color glossyReflector::path_shade(shadeRec &sr)
{
    TrekMath::vec3  wo(-sr.cast_ray.direction());
    TrekMath::vec3  wi;
    double          pdf;
    TrekMath::color fr(glossy_specular_brdf->sample_f(sr, wi, wo, pdf));
    ray             reflected_ray(sr.hitPoint, wi);
    return (fr * sr.wor->tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * glm::dot(sr.normal, wi) / pdf);
}

TrekMath::color glossyReflector::global_shade(shadeRec &sr)
{
    TrekMath::vec3 wo = -sr.cast_ray.direction();
    TrekMath::vec3 wi;
    double         pdf;
    color          fr = glossy_specular_brdf->sample_f(sr, wi, wo, pdf);
    ray            reflected_ray(sr.hitPoint, wi);
    double         NdotWi = glm::dot(sr.normal, wi);

    if (sr.depth == 0)
    {
        return fr * sr.wor->tracer_ptr->trace_ray(reflected_ray, sr.depth + 2) * NdotWi / pdf;
    }

    else
    {
        return fr * sr.wor->tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * NdotWi / pdf;
    }
}
