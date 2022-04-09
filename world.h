#pragma once

#include "bvh_node.h"
#include "hittable.h"
#include "light.h"
#include "material.h"
#include "plane.h"
#include "shadeRec.h"
#include "sphere.h"

#include <memory>
#include <vector>
//#include "tracer.h"
#include <iostream>
class tracer;
using std::make_shared;
using std::shared_ptr;

class world : public hittable
{
  public:
	world() = default;
	world(shared_ptr<hittable> object);

	void add_object(shared_ptr<hittable> object);
	void add_light(shared_ptr<light> light);
	void set_tracer_ptr(std::shared_ptr<tracer> arg_tracer_ptr);
	void clear();

  public:
	bool        hit(const ray &r, double tmin, double tmax, shadeRec &sr) const override;
	bool        bounding_box(double time0, double time1, AABB &output_box) const override;
	std::string objectType() const override;
	void        generating_acceleration_structure(double t0,double t1);

  public:
	std::shared_ptr<bvh_node> root;        // bvh tree accelerating structure
	
	std::vector<shared_ptr<hittable>> acc_structures;        // vector of  pointers to acceleration sturctures
	std::vector<shared_ptr<hittable>> objects;        // vector of  pointers to actual objects

	std::vector<shared_ptr<light>> lights;        // vector of  pointers to lights
	std::shared_ptr<light>         ambient_light_ptr;
	std::shared_ptr<tracer>        tracer_ptr;
};
