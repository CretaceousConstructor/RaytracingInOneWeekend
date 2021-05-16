#include "pointLight.h"

TrekMath::vec3 pointLight::get_direction(shadeRec& sr)
{
    auto result = glm::normalize((this->location - sr.hitPoint));

    return result; 
}
TrekMath::color pointLight::L(shadeRec& sr)
{
    return ls * cl;
}

bool pointLight::casts_shadows()
{
    return true;
}


bool pointLight::in_shadow(const ray& r, const shadeRec& sr)

{

    double t;
    this->location;
    double d = glm::length(this->location - r.origin());
    for (auto obj : sr.wor->objects) {
        if (obj->shadow_hit(r, t) && t < d) {
            return true;
        }

    }
    
    return false;
}


