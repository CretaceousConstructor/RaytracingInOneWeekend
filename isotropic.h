#pragma once

#include "tracer.h"
#include "material.h"
#include "shadeRec.h"
#include "solid_color.h"
#include "MultipleObj.h"
#include <memory>

using std::make_shared;
using std::shared_ptr;



class isotropic : public material
{
  public:
	isotropic(color c);
	isotropic(shared_ptr<texture> a);

	TrekMath::color path_shade(shadeRec &sr) override;

  private:
	shared_ptr<texture> albedo;
};
