#pragma once

#include "hittable.h"
#include "shadeRec.h"
#include "texture.h"
class material
{
  public:
	material()          = default;
	virtual ~material() = default;

	virtual TrekMath::color get_emissive_Le(shadeRec &sr);

	virtual TrekMath::color path_shade(shadeRec &sr);
	virtual TrekMath::color path_shade(shadeRec &sr, const hittable &lights);
	virtual TrekMath::color path_shade(shadeRec &sr, const hittable &objects, std::shared_ptr<hittable> lights);

	virtual TrekMath::color shade(shadeRec &sr);
	virtual TrekMath::color whitted_shade(shadeRec &sr);
	virtual TrekMath::color area_light_shade(shadeRec &sr);
	virtual TrekMath::color global_shade(shadeRec &sr);

	//virtual color           emitted(double u, double v, const point3 &p) const
	//{
	//	return color(0, 0, 0);
	//}

  protected:
	//这个是brdf的一部分，之后会更改应该。
	virtual double scattering_pdf(const shadeRec &sr, const ray &scattered);
};