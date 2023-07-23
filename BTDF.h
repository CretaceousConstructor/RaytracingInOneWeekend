#pragma once
#include <memory>
#include "colors.h"
#include "hittable.h"
#include "sampler.h"
#include "multiJittering.h"
#include "renderState.h"
class BTDF {


public:
	 virtual TrekMath::color f(const shadeRec& sr, const TrekMath::vec3& wi, const TrekMath::vec3& wo) const;//brdf函数本身
	 virtual TrekMath::color sample_f(const shadeRec& sr, const TrekMath::vec3& wo,  TrekMath::vec3& wt) const;//返回入射光线的方向(光线来的方向)
	 virtual TrekMath::color sample_f(const shadeRec& sr, const TrekMath::vec3& wo,  TrekMath::vec3& wt, double& pdf) const;
	 virtual TrekMath::color rho(const shadeRec& sr, const TrekMath::vec3& wo) const; //返回reflectance ρhh
	 virtual bool tir(const shadeRec& shade_rec) const;//判断是否是全反射
};