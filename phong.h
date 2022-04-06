#pragma once
#include "material.h"
#include "lambertian.h"
#include "glossySpecular.h"
#include "world.h"
#include "tracer.h"
class phong : public material {

public:
	phong();

	virtual TrekMath::color shade(shadeRec& sr) override;
	virtual TrekMath::color area_light_shade(shadeRec& sr) override;
	//virtual TrekMath::color whitted_shade(shadeRec& sr);
	virtual TrekMath::color path_shade(shadeRec& sr) override;
	virtual TrekMath::color global_shade(shadeRec& sr) override;


	void set_ambient_brdf(std::unique_ptr<lambertian>&& arg_ambient_brdf);
	void set_diffuse_brdf(std::unique_ptr<lambertian>&& arg_diffuse_brdf);
	void set_specular_brdf(std::unique_ptr<glossySpecular>&& arg_specular_brdf);

	void set_ambient_k(double arg_ka);
	void set_ambient_color(TrekMath::color arg_ambient_color);

	void set_diffuse_k(double arg_kd);
	void set_diffuse_color(TrekMath::color arg_diffuse_color);

	void set_specular_color(TrekMath::color arg_specular_color);
	void set_specular_k(double arg_ks);
	void set_specular_exp(double arg_exp);




	std::unique_ptr<lambertian> ambient_brdf;
	std::unique_ptr<lambertian> diffuse_brdf;
	std::unique_ptr<glossySpecular> specular_brdf;


protected:


};