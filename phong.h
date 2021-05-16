#pragma once
#include "material.h"
#include "lambertian.h"
#include "glossySpecular.h"
#include "world.h"
class phong : public material {

public:
	phong() :
		material(),
		ambient_brdf(std::make_unique<lambertian>()),
		diffuse_brdf(std::make_unique<lambertian>()),
		specular_brdf(std::make_unique<glossySpecular>())
	{
		ambient_brdf->cd = TrekMath::color(1, 1, 0.);
		ambient_brdf->kd = 0.25;  //ka


		diffuse_brdf->cd = TrekMath::color(1, 1, 0.);
		diffuse_brdf->kd = 0.25;  //kd


		specular_brdf->ks = TrekMath::color(1., 1., 0.);  //ks
		specular_brdf->exp = 1.0;
	}




	 color shade(shadeRec& sr) override;
	TrekMath::color area_light_shade(shadeRec& sr) override;


	void set_ambient_brdf(std::unique_ptr<lambertian>&& arg_ambient_brdf);
	void set_diffuse_brdf(std::unique_ptr<lambertian>&& arg_diffuse_brdf);
	void set_specular_brdf(std::unique_ptr<glossySpecular>&& arg_specular_brdf);

	void set_ka(double arg_ka);
	void set_kd(double arg_kd);
	void set_specular_exp(double arg_exp);
	void set_ambient_color(TrekMath::color arg_ambient_color);
	void set_diffuse_color(TrekMath::color arg_diffuse_color);
	void set_specular_color(TrekMath::color arg_specular_color);




	std::unique_ptr<lambertian> ambient_brdf;
	std::unique_ptr<lambertian> diffuse_brdf;
	std::unique_ptr<glossySpecular> specular_brdf;
protected:


};