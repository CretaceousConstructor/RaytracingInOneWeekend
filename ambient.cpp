#include "ambient.h"

TrekMath::vec3 ambient::get_direction(shadeRec& sr)
{
   return TrekMath::vec3(0.,0.,0.);
}

TrekMath::color ambient::L(shadeRec& sr)
{
    return ls * cl;
}

bool ambient::casts_shadows()
{
    return true;
}
