#pragma once

#include "TrekMath.h"
#include "hittable.h"
#include "world.h"
using namespace TrekMath;

class bvh_node : public hittable
{
  public:
	bvh_node() = default;

	bvh_node(const world &list, double time0, double time1) :
	    bvh_node(list.objects, 0, list.objects.size(), time0, time1)
	{}
	bvh_node(
	    const std::vector<std::shared_ptr<hittable>> &src_objects,
	    size_t start, size_t end, double time0, double time1);

	bool hit(const ray &r, double t_min, double t_max, shadeRec &sr) const override;
	bool bounding_box(double time0, double time1, AABB &output_box) const override;

	std::string objectType() const override;

  private:
	std::shared_ptr<hittable> left;
	std::shared_ptr<hittable> right;
	AABB                      box;
};
