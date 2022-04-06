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

	 color f(const shadeRec& sr, const vec3& wi, const vec3& wo) const override;//brdf��������

	 color sample_f(const shadeRec& sr, vec3& wi, const vec3& wo) const override;//����������ߵķ���(�������ķ���)

	 color sample_f(const shadeRec& sr, vec3& wi, const vec3& wo,double & pdf) const override;//����������ߵķ���(�������ķ���)


	 color rho(const shadeRec& sr, const vec3& wo) const override; //����reflectance ��hh

	TrekMath::color cr;
	double kr;
private:



};