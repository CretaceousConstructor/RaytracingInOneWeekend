#pragma once



#include "BRDF.h"
#include "multiJittering.h"
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



	color f(const shadeRec& sr, const vec3& wi, const vec3& wo) const override;//brdf函数本身 也许有问题
	color sample_f(const shadeRec& sr, vec3& wi, const vec3& wo, double& pdf) const override;//返回入射光线的方向(光线来的方向)
	color rho(const shadeRec &sr, const vec3 &wo) const override;                                    //返回reflectance ρhh
	color sample_f(const shadeRec& hit_rec, vec3& wi, const vec3& wo) const override;

    void set_samples(const int num_samples, const int num_sets, const double exp);


	TrekMath::color cs;
	double ks;
	double exp;	

private: 
	

};