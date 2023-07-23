#include "ONB.h"

TrekMath::vec3 ONB::operator[](int i) const
{
	return axis[i];
}

TrekMath::vec3 ONB::u() const
{
	return axis[0];
}

TrekMath::vec3 ONB::v() const
{
	return axis[1];
}

TrekMath::vec3 ONB::w() const
{
	return axis[2];
}

TrekMath::vec3 ONB::LocalCoordToAbsoluteWorldCoord(double a, double b, double c) const
{
	return a * u() + b * v() + c * w();
}

TrekMath::vec3 ONB::LocalCoordToAbsoluteWorldCoord(const TrekMath::vec3 &a) const
{
	return a.x * u() + a.y * v() + a.z * w();
}

void ONB::BuildFromW(const TrekMath::vec3 &n)
{
	axis[2]          = glm::normalize(n);
	const TrekMath::vec3 a = (fabs(w().x) > 0.9) ? TrekMath::vec3(0, 1, 0) : TrekMath::vec3(1, 0, 0);
	axis[1]          = glm::normalize(cross(w(), a));
	axis[0]          = cross(w(), v());
}
