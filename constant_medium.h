#pragma once

#include "hittable.h"
#include "TrekMath.h"

#include "isotropic.h"

using std::shared_ptr;
using std::make_shared;

class constant_medium: public  hittable
{
  public:
	constant_medium(shared_ptr<hittable> b, double d, shared_ptr<texture> a);

	constant_medium(shared_ptr<hittable> b, double d, color c);


	bool        hit(const ray &r, double t_min, double t_max, shadeRec &sr) const override;



	bool        bounding_box(double time0, double time1, AABB &output_box) const override;



  public:
	shared_ptr<hittable> boundary;
	shared_ptr<material> phase_function;
	double               neg_inv_density;
};
