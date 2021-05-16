#pragma once


#include "TrekMath.h"
#include "shadeRec.h"



class light
{
public:

	virtual TrekMath::vec3 get_direction(shadeRec& sr) = 0;
	virtual bool casts_shadows() = 0;
	virtual TrekMath::color L(shadeRec& sr) = 0;
	virtual bool in_shadow(const ray& r, const shadeRec& sr);
	virtual double pdf(shadeRec& sr) const;
	virtual double G(shadeRec& sr) const;
	void set_shadows_light(bool arg_shadows);


protected:
	bool shadows;
};