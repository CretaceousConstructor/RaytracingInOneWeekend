#pragma once
#include "ray.h"
#include "shadeRec.h"


class AABB
{
  public:
	AABB() = default;
	AABB(const TrekMath::point3 &a, const TrekMath::point3 &b);

	bool hit(const ray &r, double t_min, double t_max, shadeRec &sr) const;

	std::string      objectType() const;
	TrekMath::point3 min() const;
	TrekMath::point3 max() const;
	static AABB      surrounding_box(AABB box0, AABB box1);

  private:
	TrekMath::point3 minimum;
	TrekMath::point3 maximum;



};
