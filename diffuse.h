#pragma once
#include "CosinePdfHemisphere.h"
#include "HittablePdf.h"
#include "MixturePdf.h"
#include "MultipleObj.h"
#include "ONB.h"
#include "material.h"
#include "shadeRec.h"
#include "solid_color.h"
#include "tracer.h"
#include <memory>

class diffuse : public material
{
  public:
	diffuse(const color &a);
	diffuse(std::shared_ptr<texture> albedo);
	//TrekMath::color path_shade(shadeRec &sr) override;

	[[nodiscard]] TrekMath::color path_shade(shadeRec &sr, const hittable &objects, std::shared_ptr<hittable> lights) override;

  private:
	double scattering_pdf(const shadeRec &sr, const ray &scattered) override;

  private:
	std::shared_ptr<texture> albedo;
};
