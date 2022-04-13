#include "world.h"

world::world(shared_ptr<hittable> object)
{
	add_object(object);
}

bool world::hit(const ray &r, double t_min, double t_max, shadeRec &sr) const
{
	shadeRec temp_sr(*this);

	bool hit_anything   = false;
	auto closest_t_so_far = t_max;

	auto *all_objects = &objects;
	if (acc_structure_generated)
	{
		all_objects = &acc_structures;
	}

	for (const auto &object : (*all_objects))
	{
		if (object->hit(r, t_min, closest_t_so_far, temp_sr))
		{
			//auto type_object = object->objectType();

			hit_anything = true;
			if (temp_sr.t < closest_t_so_far && temp_sr.t > t_min)
			{
				closest_t_so_far = temp_sr.t;        
				sr             = temp_sr;
			}

			if (nullptr == temp_sr.mat_ptr)
			{
				std::cout << "mat_ptr is null!" << std::endl;
			}
		}
	}

	return hit_anything;
}

bool world::bounding_box(double time0, double time1, AABB &output_box) const
{
	if (objects.empty())
	{
		return false;
	}

	AABB temp_box;
	bool first_box = true;

	for (const auto &object : objects)
	{
		if (!object->bounding_box(time0, time1, temp_box))
		{
			return false;
		}
		output_box = first_box ? temp_box : AABB::surrounding_box(output_box, temp_box);
		first_box  = false;
	}

	return true;
}

void world::set_tracer_ptr(std::shared_ptr<tracer> arg_tracer_ptr)
{
	tracer_ptr = arg_tracer_ptr;
}

std::string world::objectType() const
{
	return std::string("world");
}

void world::generating_acceleration_structure(double t0, double t1)
{
	root = std::make_shared<bvh_node>(objects, 0, objects.size(), t0, t1);
	acc_structures.push_back(root);
	acc_structure_generated = true;
}

void world::clear()
{
	objects.clear();
	lights.clear();
}
void world::add_object(shared_ptr<hittable> object)
{
	objects.push_back(object);
}
void world::add_light(shared_ptr<light> light)
{
	lights.push_back(light);
}
