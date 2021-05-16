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

	virtual color f(const shadeRec& hit_rec, const vec3& wi, const vec3& wo) const override;//����brdf��������

	virtual color sample_f(const shadeRec& hit_rec, vec3& wi, const vec3& wo) const override;//���ط�����ߵķ���

	virtual color rho(const shadeRec& hit_rec, const vec3& wo) const override; //����reflectance ��hh

	double kd;
	color cd;
private:

};