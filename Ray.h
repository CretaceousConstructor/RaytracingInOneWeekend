#pragma once
#include "TrekMath.h"

class ray
{
  public:
	ray();
	ray(const TrekMath::point3 &v0, const TrekMath::vec3 &b, double para_time = 0.0);

  public:
	void                           setOrigin(const TrekMath::point3 &p);
	void                           setDir(const TrekMath::vec3 &dir);
	[[nodiscard]] double           time() const;
	[[nodiscard]] TrekMath::point3 eye() const;
	[[nodiscard]] TrekMath::point3 origin() const;

	[[nodiscard]] TrekMath::vec3 direction() const;
	[[nodiscard]] TrekMath::vec3 point_at_parameter(double t) const;

  private:
	TrekMath::point3 A;
	TrekMath::vec3   B;
	double           tm;
};