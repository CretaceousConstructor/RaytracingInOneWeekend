#pragma once

#include "TrekMath.h"
#include "hittable.h"
#include <memory>
#include <iostream>


using namespace TrekMath;
using std::shared_ptr;
using std::make_shared;

class bvh_node : public hittable
{
  public:
	bvh_node() = default;

	//bvh_node(const MultipleObj &wor, double time0, double time1);
	bvh_node(
	    const std::vector<std::shared_ptr<hittable>> &src_objects,
	    size_t start, size_t end, double time0, double time1);

	bool hit(const ray &r, double t_min, double t_max, shadeRec &sr) const override;
	bool bounding_box(double time0, double time1, AABB &output_box) const override;

	std::string object_type() const override;

  private:
	std::shared_ptr<hittable> left;         //×ó×ÓÊ÷
	std::shared_ptr<hittable> right;        //ÓÒ×ÓÊ÷
	AABB                      box;          //°üÎ§ºÐ

	static bool box_compare(const shared_ptr<hittable> a, const shared_ptr<hittable> b, int axis);

	static bool box_x_compare(const shared_ptr<hittable> a, const shared_ptr<hittable> b);

	static bool box_y_compare(const shared_ptr<hittable> a, const shared_ptr<hittable> b);

	static bool box_z_compare(const shared_ptr<hittable> a, const shared_ptr<hittable> b);




};
