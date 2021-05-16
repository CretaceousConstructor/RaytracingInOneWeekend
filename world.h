#pragma once

#include <memory>
#include <vector>
#include "hittable.h"
#include "light.h"
#include "sphere.h"
#include "plane.h"
#include "material.h"
#include "shadeRec.h"
#include <iostream>

using std::shared_ptr;
using std::make_shared;

class world : public hittable {
public:

	world() = default;
	world(shared_ptr<hittable> object) 
	{ 
		add_object(object); 
	}

	void clear() { objects.clear(); lights.clear(); }
	void add_object(shared_ptr<hittable> object) { objects.push_back(object); }
	void add_light(shared_ptr<light> light) { lights.push_back(light); }
	bool hit(const ray& r, double tmin, double tmax, shadeRec& sr) const;


	std::string objectType() const override;



public:
	std::vector< shared_ptr<hittable>> objects; // vector of  pointers
	std::vector< shared_ptr<light>> lights; // vector of  pointers
	shared_ptr<light> ambient_light_ptr;

};

