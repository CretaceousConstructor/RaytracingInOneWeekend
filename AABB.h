#pragma once
#include "ray.h"
#include "shadeRec.h"

#include <iostream>
class AABB
{
  public:
	AABB() = default;
	AABB(const TrekMath::point3 &min, const TrekMath::point3 &max);


	bool hit(const ray &r, double t_min, double t_max, shadeRec &sr) const;

	std::string      objectType() const;
	TrekMath::point3 min() const;
	TrekMath::point3 max() const;



	static AABB      surrounding_box(const AABB& box0, const AABB& box1);

  private:


	TrekMath::point3 minimum;
	TrekMath::point3 maximum;
};
