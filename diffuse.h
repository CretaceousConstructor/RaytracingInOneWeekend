#pragma once
#include "material.h"
#include "shadeRec.h"
#include "tracer.h"
#include "world.h"
#include <memory>

class diffuse : public material
{
  public:
	diffuse(const color &a);

	virtual TrekMath::color path_shade(shadeRec &sr);

  private:
	color albedo;
};
