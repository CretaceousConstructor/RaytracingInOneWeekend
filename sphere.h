#pragma once
#include "TrekMath.h"
#include "hittable.h"
using namespace TrekMath;

class sphere : public hittable
{
  public:
	sphere() = default;
	sphere(TrekMath::point3 cen, double r, std::shared_ptr<material> m);

	bool hit(const ray &r, double tmin, double tmax, shadeRec &sr) const override;
	bool shadow_hit(const ray &r, double &t_shadow) const override;
	bool bounding_box(double time0, double time1, AABB &output_box) const override;


  public:
	TrekMath::point3 center;
	double           radius;

	virtual std::string objectType() const override;

  private:
	static constexpr double kEpsilon = 0.00001;
};
