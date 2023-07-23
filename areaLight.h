#pragma once

#include "light.h"
#include "hittable.h"
#include "material.h"
#include "MultipleObj.h"
#include "shadeRec.h"
#include <memory>
class areaLight : public light {
public:

	TrekMath::vec3 get_direction(shadeRec& sr) override;
	bool in_shadow(const ray& r, const shadeRec& sr) override;
	TrekMath::color L(shadeRec& sr) override;
	double pdf(shadeRec& sr) const override;
	double G(shadeRec& sr) const override;
	bool casts_shadows() override;
	void set_object(std::shared_ptr<hittable> arg_object_ptr);

private:

	std::shared_ptr<hittable> object_ptr;
	std::shared_ptr<material> material_ptr;

	TrekMath::point3 sample_point;//sample point on the surface
	TrekMath::normal light_normal;//normal at sample point
	TrekMath::vec3 wi;//unit vector from hit point to sample point

};