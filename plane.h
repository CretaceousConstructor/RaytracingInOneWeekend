#pragma once
#include "hittable.h"


class plane : public hittable {
public:
	plane() = default;
	plane(TrekMath::point3 p, TrekMath::vec3 normalOfPlane, std::shared_ptr<material> m);

	bool hit(const ray& r, double tmin, double tmax, shadeRec& sr) const override;

	bool shadow_hit(const ray& r, double& t_shadow) const override;
	std::string object_type() const override;


public:
	TrekMath::point3 arbitraryPoint;
	TrekMath::vec3 normal;

private:
	//static constexpr double kEpsilon = 0.00001;
	static constexpr double kEpsilon = TrekMath::epsilon;


};

