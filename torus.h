#pragma once
#include "hittable.h"


class torus : public hittable {

public:


	bool hit(const ray& r, double t_min, double t_max, shadeRec& sr) const override;
	torus(const double _a, const double _b, std::shared_ptr<material> m);
	 bool shadow_hit(const ray& r, double& t_shadow) const override;

	std::string objectType() const;
		


private:
	TrekMath::normal compute_normal(const TrekMath::point3& p) const;
	double 		a;	 	// swept radius
	double		b;	 	// tube radius
	static constexpr double kEpsilon = 0.00001;

};