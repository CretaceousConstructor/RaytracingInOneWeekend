#pragma once



#include "BRDF.h"

class glossySpecular : public BRDF {
public:
	glossySpecular(
		std::unique_ptr<sampler>&& arg_sam
	)
		:
		BRDF(std::move(arg_sam))
	{

	}
	glossySpecular() = default;







	color f(const shadeRec& sr, const vec3& wi, const vec3& wo) const override;//brdf函数本身

	color sample_f(const shadeRec& sr, vec3& wi, const vec3& wo) const override//返回入射光线的方向(光线来的方向)

	{
		return TrekMath::color();
	}
	color rho(const shadeRec& sr, const vec3& wo) const override//返回reflectance ρhh
	{
		return TrekMath::color();
	}
	TrekMath::color ks;
	double exp;

private: 

};