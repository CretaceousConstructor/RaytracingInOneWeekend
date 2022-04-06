#pragma once

#include "material.h"
#include "shadeRec.h"
#include "tracer.h"
#include "world.h"
#include <memory>

class metal: public material
{ 
public:
	metal(const color &a, double f);

	virtual TrekMath::color path_shade(shadeRec &sr);

  private:
	color albedo;
	 double fuzz;
};
