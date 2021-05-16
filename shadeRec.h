#pragma once
#include <memory>
#include "TrekMath.h"
#include "ray.h"

class world;
class material;
class shadeRec {
public:
	shadeRec(const world& w)
		:
		hit_an_object(false),
		mat_ptr(nullptr),
		depth(0),
		wor(&w)
	{

	}
	shadeRec(const shadeRec& sr) = default;
	shadeRec& operator= (const shadeRec& arg_sr) = default;
	/*shadeRec& operator= (const shadeRec& arg_sr) {
		this->hitPoint =             arg_sr.hitPoint;
		this->normal =               arg_sr.normal;
		this->hit_an_object =        arg_sr.hit_an_object;
		this->mat_ptr =              arg_sr.mat_ptr;
		this->local_hitPoint =       arg_sr.local_hitPoint;
		this->front_face =           arg_sr.front_face;
		this->r =                    arg_sr.r;
		this->t =					 arg_sr.t;
		this->depth =                arg_sr.depth;
		this->dir =                  arg_sr.dir;
		this->wor =                  arg_sr.wor;
		return *this;
	}*/
	TrekMath::point3 hitPoint;
	TrekMath::vec3 normal;
	bool hit_an_object;
	std::shared_ptr<material> mat_ptr;
	TrekMath::point3 local_hitPoint;
	bool front_face;
	ray cast_ray;
	double t;
	int depth;
	TrekMath::vec3 dir;
	//const hittable_list& wor;

	const world* wor;
	
	////调整法线使得视线方向和法线总是呈现钝角
	 void set_face_normal(const ray& r, const TrekMath::vec3& outward_normal);
};

