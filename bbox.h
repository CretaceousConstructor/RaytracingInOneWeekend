#pragma once


#include "hittable.h"
class bbox : public hittable 
{
public:
	bool hit(const ray& r, double t_min, double t_max, shadeRec& sr) const override;

	std::string object_type() const override;

private:
	//static constexpr double kEpsilon = 0.00001;

	static constexpr double kEpsilon = TrekMath::epsilon;

	double x0, x1, y0, y1, z0, z1;


};