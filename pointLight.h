#pragma once
#include "light.h"
#include "shadeRec.h"
#include "world.h"

class pointLight : public light {
public:

	pointLight(TrekMath::vec3 arg_location, double arg_ls, TrekMath::color arg_cl)

		:
		light(),
		location(arg_location),
		ls(arg_ls),
		cl(arg_cl)

	{

	}
	TrekMath::vec3 get_direction(shadeRec& sr) override;

	TrekMath::color L(shadeRec& sr) override;


	bool casts_shadows() override;

	bool in_shadow(const ray& r, const shadeRec& sr) override;

private:
	//ls * cl = I radiant intensity
	TrekMath::point3 location;
	double ls;
	TrekMath::color cl;

};

