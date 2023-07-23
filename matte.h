#pragma once


#include "material.h"
#include "lambertian.h"
#include "MultipleObj.h"
#include "shadeRec.h"
#include "tracer.h"
#include <memory>
class matte : public material {


public:
	matte();

  public:

	TrekMath::color shade(shadeRec& sr) override;//without area ligh shading
	TrekMath::color area_light_shade(shadeRec& sr) override;//area light shading
	TrekMath::color global_shade(shadeRec& sr) override;
	TrekMath::color path_shade(shadeRec& sr) override;

public:

	void set_ambient_brdf(std::unique_ptr<lambertian>&& arg_ambient_brdf);
	void set_diffuse_brdf(std::unique_ptr<lambertian>&& arg_diffuse_brdf);

	void set_ambient_k(double arg_ka);
	void set_diffuse_k(double arg_kd);


	void set_ambient_color(TrekMath::color arg_ambient_color);
	void set_diffuse_color(TrekMath::color arg_diffuse_color);




private:
	std::unique_ptr<lambertian> ambient_brdf;
	std::unique_ptr<lambertian> diffuse_brdf;


};