#pragma once


#include "light.h"


class ambient : public light {
public:

	ambient()
		:light(),
		ls(1.0),
		cl(1.0, 1.0, 1.0)
	{
	}

	 TrekMath::vec3 get_direction(shadeRec& sr) override;

	 TrekMath::color L(shadeRec& sr) override ;


	 bool casts_shadows() override;

private:


	double ls;
	TrekMath::color cl;
};