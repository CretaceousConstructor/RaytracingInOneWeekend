#pragma once


#include "material.h"
#include "lambertian.h"
#include "world.h"
#include <memory>
class matte : public material {


public:
	matte() :
		material(),
		ambient_brdf(std::make_unique<lambertian>()),
		diffuse_brdf(std::make_unique<lambertian>())
	{
		ambient_brdf->cd = TrekMath::color(1, 1, 0.);
		ambient_brdf->kd = 0.15;  //ka


		diffuse_brdf->cd = TrekMath::color(1, 1, 0.);
		diffuse_brdf->kd = 0.25;  //kd


	}


	TrekMath::color shade(shadeRec& sr) override;
	TrekMath::color area_light_shade(shadeRec& sr) override;//area light shade

	void set_ambient_brdf(std::unique_ptr<lambertian>&& arg_ambient_brdf);
	void set_diffuse_brdf(std::unique_ptr<lambertian>&& arg_diffuse_brdf);

	void set_ka(double arg_ka);
	void set_kd(double arg_kd);
	void set_ambient_color(TrekMath::color arg_ambient_color);
	void set_diffuse_color(TrekMath::color arg_diffuse_color);

	std::unique_ptr<lambertian> ambient_brdf;
	std::unique_ptr<lambertian> diffuse_brdf;
private:


};