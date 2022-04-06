#pragma once

#include "BRDF.h"
class perfectSpecular : public BRDF {


public:

	perfectSpecular(
		std::unique_ptr<sampler>&& arg_sam
	)
		:
		BRDF(std::move(arg_sam))
	{
	}
	perfectSpecular() = default;

	 color f(const shadeRec& sr, const vec3& wi, const vec3& wo) const override;//brdf函数本身

	 color sample_f(const shadeRec& sr, vec3& wi, const vec3& wo) const override;//返回入射光线的方向(光线来的方向)

	 color sample_f(const shadeRec& sr, vec3& wi, const vec3& wo,double & pdf) const override;//返回入射光线的方向(光线来的方向)


	 color rho(const shadeRec& sr, const vec3& wo) const override; //返回reflectance ρhh

	TrekMath::color cr;
	double kr;
private:



};