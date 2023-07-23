#pragma once
#include <memory>
#include "colors.h"
#include "hittable.h"
#include "sampler.h"
#include "multiJittering.h"
#include "renderState.h"
class BTDF {


public:
	 virtual TrekMath::color f(const shadeRec& sr, const TrekMath::vec3& wi, const TrekMath::vec3& wo) const;//brdf��������
	 virtual TrekMath::color sample_f(const shadeRec& sr, const TrekMath::vec3& wo,  TrekMath::vec3& wt) const;//����������ߵķ���(�������ķ���)
	 virtual TrekMath::color sample_f(const shadeRec& sr, const TrekMath::vec3& wo,  TrekMath::vec3& wt, double& pdf) const;
	 virtual TrekMath::color rho(const shadeRec& sr, const TrekMath::vec3& wo) const; //����reflectance ��hh
	 virtual bool tir(const shadeRec& shade_rec) const;//�ж��Ƿ���ȫ����
};