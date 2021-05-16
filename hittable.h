#pragma once
#include "ray.h"
#include "shadeRec.h"

#include <memory>
#include <string>

class bbox;
class hittable {
public:
	//,
	//mat_ptr(nullptr)
	hittable()
		:
		shadows(true)
	{
	}
protected:

	hittable(std::shared_ptr<material> arg_mat_ptr)
		:
		shadows(true),
		mat_ptr(arg_mat_ptr)
	{
	}




public:
	virtual bool hit(const ray& r, double t_min, double t_max, shadeRec& sr) const = 0;
	virtual std::string objectType() const = 0;
	virtual bool shadow_hit(const ray& r, double& t_shadow) const {
		return false;
	}
	virtual TrekMath::point3 sample() {
		return TrekMath::point3();
	}
	virtual TrekMath::normal get_normal(const TrekMath::point3& p) {

		return TrekMath::vec3();

	}
	virtual double pdf(shadeRec& sr) {
		return 1.0;
	}


	void set_shadows_object(bool arg_shadows)
	{
		shadows = arg_shadows;
	}

	std::shared_ptr<material> get_mat_ptr() {
		return mat_ptr;
	}

	void set_material(std::shared_ptr<material> arg_mat)
	{
		mat_ptr = arg_mat;
	}

	virtual bbox get_bounding_box() {
		return bbox();
	}


protected:
	bool shadows;
	std::shared_ptr<material> mat_ptr = nullptr;

};