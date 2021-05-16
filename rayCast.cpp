#include "rayCast.h"

rayCast::rayCast(const world* const world)
	:tracer(world)

{


}



color rayCast::trace_ray(const ray& r) const
{
	//hit_record rec;
	shadeRec sr(*world_ptr);
	////too many bounces
	//if (argument_depth <= 0) {
	//	return TrekMath::color(0.0, 0.0, 0.0);
	//}

	if (world_ptr->hit(r, epsilon, infinity,sr)) {

		return sr.mat_ptr->shade(sr);
		
	}
	else {

		return TrekMath::color(1.,1.,1.);
		//if the ray Didn't hit anything
		//using interpolation to generate background color or envirenment lighting
		//if the ray didn't hit anything,background color will be returned;
		vec3 unit_direction = glm::normalize((r.direction()));
		auto t = 0.5 * (unit_direction.y + 1.0);
		return (1.0 - t) * TrekMath::color(1.0, 1.0, 1.0) + t * TrekMath::color(0.5, 0.7, 1.0);



	}
}

color rayCast::trace_ray(const ray& r, int argument_depth) const
{
	return color();
}
