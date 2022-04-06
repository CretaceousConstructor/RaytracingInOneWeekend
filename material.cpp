#include "material.h"

TrekMath::color material::shade(shadeRec& sr)
{
    return TrekMath::color();
}

TrekMath::color material::area_light_shade(shadeRec& sr)
{
    return TrekMath::color();
}

TrekMath::color material::get_emissive_Le(shadeRec& sr)
{
    return TrekMath::color();
}

color material::whitted_shade(shadeRec& sr)
{
    return color();
}

color material::path_shade(shadeRec& sr)
{
    return color();
}

TrekMath::color material::global_shade(shadeRec& sr)
{
    return TrekMath::color();
}
