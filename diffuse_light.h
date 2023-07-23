#pragma once
#include "material.h"
#include "solid_color.h"
using std::make_shared;
using std::shared_ptr;

class diffuse_light : public material
{
  public:
	diffuse_light(shared_ptr<texture> a);
	diffuse_light(color c);

	TrekMath::color path_shade(shadeRec &sr) override;
	TrekMath::color path_shade(shadeRec &sr, const hittable &lights) override;
	TrekMath::color path_shade(shadeRec &sr, const hittable &objects, std::shared_ptr<hittable> lights) override;


  public:
	shared_ptr<texture> emit;
};
