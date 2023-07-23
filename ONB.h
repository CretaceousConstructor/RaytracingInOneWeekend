#pragma once
#include "TrekMath.h"

class ONB
{
  public:
	ONB() =default;

	inline TrekMath::vec3 operator[](int i) const;

	[[nodiscard]] TrekMath::vec3 u() const;
	[[nodiscard]] TrekMath::vec3 v() const;
	[[nodiscard]] TrekMath::vec3 w() const;

	[[nodiscard]] TrekMath::vec3 LocalCoordToAbsoluteWorldCoord(double a, double b, double c) const;

	[[nodiscard]] TrekMath::vec3 LocalCoordToAbsoluteWorldCoord(const TrekMath::vec3 &a) const;

	void BuildFromW(const TrekMath::vec3 &);
  public:
	TrekMath::vec3 axis[3];

};
