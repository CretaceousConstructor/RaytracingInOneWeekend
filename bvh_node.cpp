#include "bvh_node.h"

//bvh_node::bvh_node(const MultipleObj &wor, double time0, double time1) :
//    bvh_node(wor.objects, 0, wor.objects.size(), time0, time1)
//{}

bvh_node::bvh_node(const std::vector<std::shared_ptr<hittable>> &src_objects, size_t start, size_t end, double time0, double time1)
{
	auto objects = src_objects;        // Create a modifiable array of the source scene objects

	int  axis       = random_int(0, 2);        //随机从 x y z轴中选择一个轴
	auto comparator = (axis == 0) ? box_x_compare : (axis == 1) ? box_y_compare : box_z_compare;

	size_t object_span = end - start;        //物体数目

	if (object_span == 1)
	{
		left = right = objects[start];        //当仅有一个node的时候，直接进行复制
	}
	else if (object_span == 2)
	{
		if (comparator(objects[start], objects[start + 1]))
		{
			left  = objects[start];
			right = objects[start + 1];
		}
		else
		{
			left  = objects[start + 1];
			right = objects[start];
		}
	}
	else
	{
		std::sort(objects.begin() + start, objects.begin() + end, comparator);

		auto mid = start + object_span / 2;
		left     = make_shared<bvh_node>(objects, start, mid, time0, time1);
		right    = make_shared<bvh_node>(objects, mid, end, time0, time1);
	}

	AABB box_left, box_right;

	if (!left->bounding_box(time0, time1, box_left) || !right->bounding_box(time0, time1, box_right))
	{
		std::cerr << "No bounding box in bvh_node constructor.\n";
	}

	box = AABB::surrounding_box(box_left, box_right);
}

bool bvh_node::hit(const ray &r, double t_min, double t_max, shadeRec &sr) const
{

	if (!box.hit(r, t_min, t_max, sr))
	{
		return false;
	}


	//只有在碰到子节点（非bvh节点）的时候，shadeRec才会被填入
	bool hit_left  = left->hit(r, t_min, t_max, sr);
	bool hit_right = right->hit(r, t_min, hit_left ? sr.t : t_max, sr);

	return hit_left || hit_right;
}

bool bvh_node::bounding_box(double time0, double time1, AABB &output_box) const
{
	output_box = box;
	return true;
}

std::string bvh_node::object_type() const
{
	return std::string("bvh node");
}

bool bvh_node::box_compare(const shared_ptr<hittable> a, const shared_ptr<hittable> b, int axis)
{
	AABB box_a;
	AABB box_b;

	if (!a->bounding_box(0, 0, box_a) || !b->bounding_box(0, 0, box_b))
		std::cerr << "No bounding box in bvh_node constructor.\n";

	return box_a.min()[axis] < box_b.min()[axis];
}

bool bvh_node::box_x_compare(const shared_ptr<hittable> a, const shared_ptr<hittable> b)
{
	return box_compare(a, b, 0);
}

bool bvh_node::box_y_compare(const shared_ptr<hittable> a, const shared_ptr<hittable> b)
{
	return box_compare(a, b, 1);
}

bool bvh_node::box_z_compare(const shared_ptr<hittable> a, const shared_ptr<hittable> b)
{
	return box_compare(a, b, 2);
}
