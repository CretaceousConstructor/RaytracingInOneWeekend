#pragma once

#include "colors.h"
#include "shadeRec.h"
#include "renderState.h"


class material
{
  public:
	material()          = default;
	virtual ~material() = default;



	virtual TrekMath::color get_emissive_Le(shadeRec &sr);

	virtual TrekMath::color shade(shadeRec &sr);
	virtual TrekMath::color whitted_shade(shadeRec &sr);
	virtual TrekMath::color path_shade(shadeRec &sr);
	virtual TrekMath::color area_light_shade(shadeRec &sr);
	virtual TrekMath::color global_shade(shadeRec &sr);




};