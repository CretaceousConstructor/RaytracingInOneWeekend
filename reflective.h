#pragma once

#include "world.h"
#include "phong.h"
#include "perfectSpecular.h"
#include "tracer.h"
class reflective : public phong {
public:
	reflective() :
		phong(),
		reflective_brdf(std::make_unique<perfectSpecular>())
	{
	}

	void set_reflective_k(double arg_kr);
	void set_reflective_color(TrekMath::color arg_cr);




public:
	TrekMath::color shade(shadeRec& sr) override;
	TrekMath::color area_light_shade(shadeRec& sr) override;
	TrekMath::color path_shade(shadeRec& sr) override;
	TrekMath::color global_shade(shadeRec& sr) override;

private:
	std::unique_ptr<perfectSpecular> reflective_brdf;


};
