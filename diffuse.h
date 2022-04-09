#pragma once
#include "material.h"
#include "shadeRec.h"
#include "tracer.h"
#include <memory>

class diffuse : public material
{
  public:
	diffuse() = default;
	diffuse(std::shared_ptr<texture> albedo);
	virtual TrekMath::color path_shade(shadeRec &sr);

  private:
	std::shared_ptr<texture> albedo;
};
