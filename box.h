#pragma once


#include "hittable.h"
class box : public hittable {
public:
	bool hit(const ray& r, double t_min, double t_max, shadeRec& sr) const override;

	std::string objectType() const override;
private:
	TrekMath::normal get_face_nornal(const int face_int) const;
	static constexpr double kEpsilon = 0.00001;
	double x0, x1, y0, y1, z0, z1;


};