#pragma once
#include "colors.h"
#include "hittable.h"
#include "multiJittering.h"
#include "renderState.h"
#include "sampler.h"
#include <memory>
using namespace TrekMath;
class BRDF
{
  public:
	BRDF() :
	    sam(std::make_unique<multiJittering>(1, 2))
	{
	}
	BRDF(
	    std::unique_ptr<sampler> &&arg_sam) :
	    sam(std::move(arg_sam))
	{
	}

  public:
	virtual color f(const shadeRec &hit_rec, const vec3 &wi, const vec3 &wo) const;        //brdf��������

	virtual color sample_f(const shadeRec &hit_rec, vec3 &wi, const vec3 &wo) const;        //����������ߵķ���(�������ķ���)

	virtual color rho(const shadeRec &hit_rec, const vec3 &wo) const;        //����reflectance ��hh

	virtual color sample_f(const shadeRec &hit_rec, vec3 &wi, const vec3 &wo, double &pdf) const;

  public:
	void set_samples(std::unique_ptr<sampler> &&arg_sam);

  protected:
	std::unique_ptr<sampler> sam;
};