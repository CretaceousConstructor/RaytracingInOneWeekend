#include "constant_medium.h"


constant_medium::constant_medium(shared_ptr<hittable> b, double d, shared_ptr<texture> a) :
    boundary(b),
    neg_inv_density(-1 / d),
    phase_function(make_shared<isotropic>(a))
{
}

constant_medium::constant_medium(shared_ptr<hittable> b, double d, color c) :
    boundary(b),
    neg_inv_density(-1 / d),
    phase_function(make_shared<isotropic>(c))
{}

bool constant_medium::hit(const ray &r, double t_min, double t_max, shadeRec &sr) const
{
	shadeRec rec1(*(sr.wor));
	shadeRec rec2(*(sr.wor));

	if (!boundary->hit(r, -TrekMath::infinity, TrekMath::infinity, rec1))
	{
		return false;
	}

	if (!boundary->hit(r, rec1.t + 0.0001, TrekMath::infinity, rec2))
	{
		return false;
	}
	if (rec1.t < t_min)
	{
		rec1.t = t_min;
	}
	if (rec2.t > t_max)
	{
		rec2.t = t_max;
	}

	if (rec1.t >= rec2.t)
	{
		return false;
	}
	if (rec1.t < 0)
	{
		rec1.t = 0;
	}
	const auto ray_length               = glm::length(r.direction());
	const auto distance_inside_boundary = (rec2.t - rec1.t) * ray_length;
	const auto hit_distance             = neg_inv_density * log(random_double());

	if (hit_distance > distance_inside_boundary)        //光线直接穿过去了
	{
		return false;
	}

	sr.t        = rec1.t + hit_distance / ray_length;
	sr.hitPoint = r.point_at_parameter(sr.t);
	sr.normal     = vec3(1, 0, 0);        // arbitrary
	sr.front_face = true;                 // also arbitrary
	sr.mat_ptr    = phase_function;

	return true;


}

bool constant_medium::bounding_box(double time0, double time1, AABB &output_box) const
{
	return boundary->bounding_box(time0, time1, output_box);
}
