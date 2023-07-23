#pragma once
#include "BTDF.h"
class perfectTransmitter : public BTDF {


public:
	perfectTransmitter() = default;

	TrekMath::color sample_f(const shadeRec&sr, const TrekMath::vec3&wo, TrekMath::vec3&wt) const override; //返回入射光线的方向(光线来的方向)

	bool tir(const shadeRec& shade_rec) const override;
	double ior;
	double kt;
private:
};