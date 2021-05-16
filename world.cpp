#include "world.h"

bool world::hit(const ray& r, double t_min, double t_max, shadeRec& sr) const {


	//hit_record temp_rec;
	shadeRec temp_sr(*this);

	bool hit_anything = false;
	auto closest_so_far = t_max;

	for (const auto& object : objects) {


		if (object->hit(r, t_min, closest_so_far, temp_sr)) {

			auto type_object = object->objectType();
			if (type_object == std::string("plane")) {

				hit_anything = true;

			}

			hit_anything = true;
			closest_so_far = temp_sr.t; //temp_sr
			sr = temp_sr;
			if (temp_sr.mat_ptr == nullptr) {

				std::cout << "mat_ptr is null!";

			}
		}
	}

	return hit_anything;
}

std::string world::objectType() const
{
	return std::string("world");
}
