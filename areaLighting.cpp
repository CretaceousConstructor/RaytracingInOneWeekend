#include "areaLighting.h"

areaLighting::areaLighting(const world* const world)
	:tracer(world)

{


}

color areaLighting::trace_ray(const ray& r) const
{
	//hit_record rec;
	shadeRec sr(*world_ptr);

	if (world_ptr->hit(r, TrekMath::epsilon, TrekMath::infinity, sr)) {

		return sr.mat_ptr->area_light_shade(sr);

	}
	else {


		//if the ray Didn't hit anything
		//using interpolation to generate background color or
		//if the ray didn't hit anything,background color will be returned;
		vec3 unit_direction = glm::normalize((r.direction()));
		auto t = 0.5 * (unit_direction.y + 1.0);
		return (1.0 - t) * TrekMath::color(0.5, 0.5, 0.5) + t * TrekMath::color(0.25, 0.35, 0.5);



	}
}

color areaLighting::trace_ray(const ray& r, int argument_depth) const
{
	return color();
}


