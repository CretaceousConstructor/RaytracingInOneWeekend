#pragma once

#include "material.h"
#include "shadeRec.h"
#include "tracer.h"
#include "MultipleObj.h"
#include <memory>

class dielectric : public material
{
  public:
	dielectric(double index_of_refraction) :
	    ir(index_of_refraction)
	{}

	virtual TrekMath::color path_shade(shadeRec &sr) override;

  private:
	static double reflectance(double cosine, double ref_idx);
	double ir;        // Index of Refraction
};
