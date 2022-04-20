#pragma once

#include "hittable.h"

class triangle : public hittable {


public:
	triangle() = default;
	triangle(TrekMath::point3 arg_a, TrekMath::point3 arg_b, TrekMath::point3 arg_c, std::shared_ptr<material> arg_mat);
	bool hit(const ray& r, double t_min, double t_max, shadeRec& sr) const override;
	std::string object_type() const override;

	bool shadow_hit(const ray& r, double& t_shadow) const override;


private:

	TrekMath::point3 v0;
	TrekMath::point3 v1;
	TrekMath::point3 v2;
	TrekMath::normal nor;
	//static constexpr double kEpsilon = 0.00001;

	static constexpr double kEpsilon = TrekMath::epsilon;

};