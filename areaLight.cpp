#include "areaLight.h"

TrekMath::vec3 areaLight::get_direction(shadeRec& sr)
{
    sample_point = object_ptr->sample();

    light_normal = object_ptr->get_normal(sample_point);

    wi = sample_point - sr.hitPoint;
    wi = glm::normalize(wi);

    return wi;

}

bool areaLight::in_shadow(const ray& r, const shadeRec& sr)
{
    double t;
    double ts = glm::dot((sample_point - r.origin()) ,r.direction() );
    //double length = glm::length(sample_point - r.origin());lenght可以被用来替换ts
    

    for (auto obj : sr.wor->objects) {
        if (obj->shadow_hit(r, t) && t < ts) {
            return true;
        }
    }
    return false;
    
}

TrekMath::color areaLight::L(shadeRec& sr)
{
    double nDotd = glm::dot(-light_normal,wi);
    if (nDotd > 0.) {
        return (material_ptr->get_emissive_Le(sr));
    }

    else
    {
        return TrekMath::color(0.,0.,0.);
    }


}

double areaLight::pdf(shadeRec& sr) const
{
    return (object_ptr->pdf(sr));
}

double areaLight::G(shadeRec& sr) const
{
    double nDotd = glm::dot(-light_normal,wi);
    double d2 = glm::length2(sample_point-sr.hitPoint);

    return nDotd / d2;
}

bool areaLight::casts_shadows()
{
    return true;
}

void areaLight::set_object(std::shared_ptr<hittable> arg_object_ptr)
{
    object_ptr = arg_object_ptr;

    material_ptr = arg_object_ptr->get_mat_ptr();

}
