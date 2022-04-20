#include "disk.h"

disk::disk(TrekMath::point3 arg_cen, double arg_radius, TrekMath::normal arg_nor, std::shared_ptr<material> m)
	:hittable(m),
	center(arg_cen),
	radius(arg_radius),
	nor(arg_nor)
{
}

bool disk::hit(const ray& r, double t_min, double t_max, shadeRec& sr) const
{
	double t = glm::dot(center - r.origin(), nor) / glm::dot(r.direction(), nor);

	if (abs(t) <= kEpsilon) {
		return false;
	}

	TrekMath::point3 p = r.point_at_parameter(t);
	if (glm::length2(center - p) < (radius * radius)) {

		sr.set_front_face_and_normal(r,nor);
		sr.mat_ptr = mat_ptr;
		sr.cast_ray = r;
		sr.hitPoint = p;
		sr.local_hitPoint = p;
		sr.hit_an_object = true;
		sr.t = t;

		return true;
	}
	else {
		return false;
	}


}

std::string disk::object_type() const
{
	return std::string("disk");
}
