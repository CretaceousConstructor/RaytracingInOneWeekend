#include "whitted.h"

whitted::whitted(const world* const world)
    :tracer(world)
{
}

color whitted::trace_ray(const ray& r) const
{
    return color();
}

color whitted::trace_ray(const ray& r,int depth) const
{
    if (depth > DefaultRenderState::max_depth) {

        return color(0.,0.,0.);
    }
    else {
        shadeRec sr(*world_ptr);

        if (world_ptr->hit(r, epsilon, infinity, sr)) {
            sr.depth = depth;
            return sr.mat_ptr->shade(sr);
        }
        else {
            vec3 unit_direction = glm::normalize((r.direction()));
            auto t = 0.5 * (unit_direction.y + 1.0);
            return (1.0 - t) * TrekMath::color(1.0, 1.0, 1.0) + t * TrekMath::color(0.5, 0.7, 1.0);
        }


    }


}
