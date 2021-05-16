#pragma once

#include "BRDF.h"
class lambertian : public BRDF {

public:
	lambertian(
		std::unique_ptr<sampler>&& arg_sam
	)
		:
		BRDF(std::move(arg_sam))
	{

	}
	lambertian() = default;

	virtual color f(const shadeRec& hit_rec, const vec3& wi, const vec3& wo) const override;//返回brdf函数本身

	virtual color sample_f(const shadeRec& hit_rec, vec3& wi, const vec3& wo) const override;//返回反射光线的方向

	virtual color rho(const shadeRec& hit_rec, const vec3& wo) const override; //返回reflectance ρhh

	double kd;
	color cd;
private:

};