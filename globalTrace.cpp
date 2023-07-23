#include "globalTrace.h"



globalTrace::globalTrace(const MultipleObj* const world)
	:tracer(world)

{


}

color globalTrace::trace_ray(const ray& r) const
{
	return color();
}

TrekMath::color globalTrace::trace_ray(const ray& r, int argument_depth) const
{
	if (argument_depth > DefaultRenderState::max_depth) {
		return TrekMath::color(0., 0., 0.);
	}
	else {
		shadeRec sr(*world_ptr);

		if (world_ptr->hit(r, epsilon, infinity, sr)) {
			sr.depth = argument_depth;
			return sr.mat_ptr->global_shade(sr);
		}
		else {
			//vec3 unit_direction = glm::normalize((r.direction()));
			//auto t = 0.5 * (unit_direction.y + 1.0);
			//return (1.0 - t) * TrekMath::color(1.0, 1.0, 1.0) + t * TrekMath::color(0.5, 0.7, 1.0);
			return color(0., 0., 0.);
		}



	}


}
