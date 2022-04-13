#pragma once
#include "light.h"
#include "TrekMath.h"
#include "sampler.h"
#include "colors.h"
#include "world.h"
#include "ray.h"
#include "multiJittering.h"
#include "renderState.h"
#include <memory>
class ambientOccluder : public light {

public:
	//DefaultRenderState::view_plane_samples_per_pixel = 25;
	//view_plane_sample_sets = 83;
	ambientOccluder() 
		:
		min_amount(0.),
		sampler_ptr(std::make_unique<multiJittering>(1, 2)),
		cl(.5, .5, .5),
		ls(0.2)
	{ 
	}
	bool in_shadow(const ray& r, const shadeRec& sr) override;
	TrekMath::color L(shadeRec& sr) override;

	void set_sampler(std::unique_ptr<sampler>&& s_ptr);

	virtual bool casts_shadows() override {
		return true;
	}
	

	TrekMath::color cl;
	double ls;
	double min_amount;
private:
	TrekMath::vec3 get_direction(shadeRec& sr) override;
	TrekMath::vec3	 u, v, w;
	std::unique_ptr<sampler> sampler_ptr;
	

};