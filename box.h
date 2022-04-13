#pragma once

#include "hittable.h"
#include "AABB.h"

class box : public hittable {
public:
	box(TrekMath::point3 p0, TrekMath::point3 p1,std::shared_ptr<material> m);
	bool hit(const ray& r, double t_min, double t_max, shadeRec& sr) const override;



	bool bounding_box(double time0, double time1, AABB &output_box) const override;




	std::string objectType() const override;
private:
	TrekMath::normal get_face_nornal(const int face_int) const;
	static constexpr double kEpsilon = 0.00001;
	double x0, x1, y0, y1, z0, z1;

	TrekMath::point3 minimum;
	TrekMath::point3 maximum;

};