#pragma once
#include "TrekMath.h"
#include "hittable.h"

using namespace TrekMath;
class movingSphere : public hittable

{
  public:
	movingSphere() = default;

	movingSphere(
	    TrekMath::point3 cen0, TrekMath::point3 cen1, double _time0, double _time1, double r, std::shared_ptr<material> m);

	bool hit(const ray &r, double tmin, double tmax, shadeRec &sr) const override;
	bool shadow_hit(const ray &r, double &t_shadow) const override;
	bool bounding_box(double time0, double time1, AABB &output_box) const override;

	virtual std::string objectType() const override;

	TrekMath::point3 center(double time) const;

  private:
	TrekMath::point3          center0, center1;
	double                    time0, time1;
	double                    radius;
	std::shared_ptr<material> mat_ptr;
};
