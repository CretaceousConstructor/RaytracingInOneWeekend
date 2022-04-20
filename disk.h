#pragma once
#include "hittable.h"
#include "TrekMath.h"
class disk : public hittable {



public:
	disk(TrekMath::point3 arg_cen, double arg_radius, TrekMath::normal arg_nor, std::shared_ptr<material> m);
	virtual bool hit(const ray& r, double t_min, double t_max, shadeRec& sr) const;
	virtual std::string object_type() const ;
private:
	TrekMath::point3 center;
	double radius;
	TrekMath::normal nor;
	//static constexpr double kEpsilon = 0.00001;

	static constexpr double kEpsilon = TrekMath::epsilon;

};