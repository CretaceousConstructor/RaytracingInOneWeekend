#include "pathTrace.h"

pathTrace::pathTrace(const world* const world)
	:tracer(world)

{


}

color pathTrace::trace_ray(const ray& r) const
{
	return color();
}

TrekMath::color pathTrace::trace_ray(const ray& r, int argument_depth) const
{
	if (argument_depth > renderState::max_depth) {
		return TrekMath::color(0., 0., 0.);
	}
	else {
		shadeRec sr(*world_ptr);

		if (world_ptr->hit(r, epsilon, infinity, sr)) {
			sr.depth = argument_depth;
			return sr.mat_ptr->path_shade(sr);
		}
		else {
			vec3 unit_direction = glm::normalize((r.direction()));
			auto t = 0.5 * (unit_direction.y + 1.0);
			return (1.0 - t) * TrekMath::color(1.0, 1.0, 1.0) + t * TrekMath::color(0.5, 0.7, 1.0);
		}

	}


}
