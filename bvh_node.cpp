#include "bvh_node.h"

bool bvh_node::hit(const ray &r, double t_min, double t_max, shadeRec &sr) const
{
	if (!box.hit(r, t_min, t_max, sr))
	{
		return false;
	}

	bool hit_left  = left->hit(r, t_min, t_max, sr);
	bool hit_right = right->hit(r, t_min, hit_left ? sr.t : t_max, sr);

	return hit_left || hit_right;
}

bool bvh_node::bounding_box(double time0, double time1, AABB &output_box) const
{
	output_box = box;
	return true;
}

std::string bvh_node::objectType() const
{
	return std::string("bvh node");
}
