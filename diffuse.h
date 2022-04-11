#pragma once
#include "material.h"
#include "shadeRec.h"
#include "tracer.h"
#include "solid_color.h"
#include <memory>

class diffuse : public material
{
  public:
	diffuse() = default; 
	diffuse(const color &a);
	diffuse(std::shared_ptr<texture> albedo);
	TrekMath::color path_shade(shadeRec &sr) override;

  private:
	std::shared_ptr<texture> albedo;
};
