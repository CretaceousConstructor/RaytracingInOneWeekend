#pragma once
#include <memory>
#include "colors.h"
#include "hittable.h"
#include "sampler.h"
#include "multiJittering.h"
#include "renderState.h"
class BRDF {
public:
	BRDF():
		sam(std::make_unique<multiJittering>(DefaultRenderState::samples_per_set, DefaultRenderState::view_plane_sample_sets))
	{
	}
	BRDF(
		std::unique_ptr<sampler>&& arg_sam
	)
		:
		sam(std::move(arg_sam))
	{
	}


public:
	virtual color f(const shadeRec& hit_rec, const vec3& wi, const vec3& wo) const;//brdf函数本身

	virtual color sample_f(const shadeRec& hit_rec, vec3& wi, const vec3& wo) const;//返回入射光线的方向(光线来的方向)

	virtual color rho(const shadeRec& hit_rec,const vec3& wo) const; //返回reflectance ρhh

	virtual color sample_f(const shadeRec& hit_rec, vec3& wi, const vec3& wo, double& pdf) const;
public:
    void set_samples(std::unique_ptr<sampler>&& arg_sam);
protected:
	std::unique_ptr<sampler> sam;



};