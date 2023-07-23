#include "pathTracer.h"

pathTracer::pathTracer(const MultipleObj *const world) :
    tracer(world)
{

}

color pathTracer::trace_ray(const ray &r) const
{
	return color{};
}

TrekMath::color pathTracer::trace_ray(const ray &r, int argument_depth) const
{
	if (argument_depth > DefaultRenderState::max_depth)
	{
		return TrekMath::color{0., 0., 0.};
	}
	else
	{
		shadeRec sr(*world_ptr);

		if (world_ptr->hit(r, epsilon, infinity, sr))
		{
			sr.depth = argument_depth;
			return sr.mat_ptr->path_shade(sr);
		}
		else
		{
			return background;
			//vec3 unit_direct
			// backgrounion = glm::normalize((r.direction()));
			//auto t = 0.5 * (unit_direction.y + 1.0);
			//return (1.0 - t) * TrekMath::color(1.0, 1.0,& 1.0) + t * TrekMath::color(0.5, 0.7, 1.0);
		}
	}
}

TrekMath::color pathTracer::trace_ray(const ray &r, const hittable &objects, int argument_depth) const
{
	if (argument_depth > DefaultRenderState::max_depth)
	{
		return TrekMath::color{0., 0., 0.};
	}
	else
	{
		shadeRec sr{};

		if (objects.hit(r, epsilon, infinity, sr))
		{
			sr.depth = argument_depth;
			return sr.mat_ptr->path_shade(sr);
		}
		else
		{
			return background;
		}
	}
}

color pathTracer::trace_ray(const ray &r, const hittable &objects, const hittable &lights, int argument_depth) const
{
	if (argument_depth > DefaultRenderState::max_depth)
	{
		return TrekMath::color{0., 0., 0.};
	}
	else
	{
		shadeRec sr{};

		if (objects.hit(r, epsilon, infinity, sr))
		{
			sr.depth = argument_depth;
			return sr.mat_ptr->path_shade(sr, lights);
		}
		else
		{
			return background;
		}
	}
}

color pathTracer::trace_ray(const ray &r, const hittable &objects, std::shared_ptr<hittable> lights, int argument_depth) const
{
	if (argument_depth > DefaultRenderState::max_depth)
	{
		return TrekMath::color{0., 0., 0.};
	}
	else
	{
		shadeRec sr{};

		if (objects.hit(r, epsilon, infinity, sr))
		{
			sr.depth = argument_depth;
			return sr.mat_ptr->path_shade(sr, objects, lights);
		}
		else
		{
			return background;
		}
	}
}
