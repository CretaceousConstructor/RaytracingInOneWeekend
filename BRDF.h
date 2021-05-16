#pragma once
#include <memory>
#include "colors.h"
#include "hittable.h"
#include "sampler.h"
class BRDF {
public:
	BRDF() = default;
	BRDF(
		std::unique_ptr<sampler>&& arg_sam
	)
		:
		sam(std::move(arg_sam))
	{

	}


public:
	virtual color f(const shadeRec& hit_rec, const vec3& wi, const vec3& wo) const = 0;//brdf函数本身

	virtual color sample_f(const shadeRec& hit_rec, vec3& wi, const vec3& wo) const = 0;//返回入射光线的方向(光线来的方向)

	virtual color rho(const shadeRec& hit_rec,const vec3& wo) const = 0; //返回reflectance ρhh

protected:

	std::unique_ptr<sampler> sam;


};