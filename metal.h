#pragma once

#include "material.h"
#include "shadeRec.h"
#include "tracer.h"
#include "MultipleObj.h"
#include <memory>

class metal: public material
{ 
public:
	metal(const color &a, double f);

	virtual TrekMath::color path_shade(shadeRec &sr) override;

  private:
	color albedo;
	 double fuzz;
};
