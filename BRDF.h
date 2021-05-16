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
	virtual color f(const shadeRec& hit_rec, const vec3& wi, const vec3& wo) const = 0;//brdf��������

	virtual color sample_f(const shadeRec& hit_rec, vec3& wi, const vec3& wo) const = 0;//����������ߵķ���(�������ķ���)

	virtual color rho(const shadeRec& hit_rec,const vec3& wo) const = 0; //����reflectance ��hh

protected:

	std::unique_ptr<sampler> sam;


};