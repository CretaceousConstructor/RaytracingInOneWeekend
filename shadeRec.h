#pragma once
#include "ray.h"
#include <memory>

class world;
class material;

class shadeRec
{
  public:
	shadeRec(const world &w);
	shadeRec(const shadeRec &sr) = default;
	shadeRec &operator=(const shadeRec &arg_sr) = default;
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
	TrekMath::point3          hitPoint;
	TrekMath::point3          local_hitPoint;        //used for texturing
	TrekMath::normal          normal;
	std::shared_ptr<material> mat_ptr;
	bool                      hit_an_object;
	bool                      front_face;
	double                    t;
	int                       depth;
	TrekMath::texcoor2d                 texcor;

	ray                       cast_ray;
	//TrekMath::vec3            dir;


	const world *wor;

	//调整法线,使得视线方向和法线总是呈现钝角，并且判断ray的起点在物体内部还是外部。
	void set_front_face_and_normal(const ray &r, const TrekMath::vec3 &outward_normal);
};
