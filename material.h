#pragma once

#include "colors.h"
#include "shadeRec.h"
class material {
public:
	material() = default;

	virtual TrekMath::color shade(shadeRec& sr) = 0;//point and directional light shade
	virtual TrekMath::color area_light_shade(shadeRec& sr) = 0;//area light shade
	virtual TrekMath::color get_emissive_Le(shadeRec& sr);  //
	/*virtual color whitted_shade(shadeRec& sr) ;
	virtual color path_shade(shadeRec& sr) ;*/


};