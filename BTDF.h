#pragma once
#include <memory>
#include "colors.h"
#include "hittable.h"
#include "sampler.h"
#include "multiJittering.h"
#include "renderState.h"
class BTDF {


public:
	 virtual color f(const shadeRec& sr, const vec3& wi, const vec3& wo) const;//brdf��������
	 virtual color sample_f(const shadeRec& sr, const vec3& wo,  vec3& wt) const;//����������ߵķ���(�������ķ���)
	 virtual color sample_f(const shadeRec& sr, const vec3& wo,  vec3& wt, double& pdf) const;
	 virtual color rho(const shadeRec& sr, const vec3& wo) const; //����reflectance ��hh
	 virtual bool tir(const shadeRec& shade_rec) const;//�ж��Ƿ���ȫ����
};