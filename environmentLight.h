#pragma once

#include "light.h"
#include "sampler.h"
#include "material.h"
#include "shadeRec.h"
#include "MultipleObj.h"
#include <memory>
class environmentLight : public light {
public:




	void set_sampler(std::unique_ptr<sampler>&& arg_sampler_ptr);
	void set_material(std::shared_ptr<material>&& arg_material_ptr);
	TrekMath::vec3 get_direction(shadeRec& sr) override;
	TrekMath::color L(shadeRec& sr) override;
	bool in_shadow(const ray& r, const shadeRec& sr) override;
	double pdf( shadeRec& sr) const override;
	bool casts_shadows() override {
		return true;
	}


private:
	std::unique_ptr<sampler> sampler_ptr;
	std::shared_ptr<material> material_ptr;
	TrekMath::vec3 u, v, w;
	TrekMath::vec3 wi;

};