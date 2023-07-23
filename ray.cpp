#include "ray.h"

ray::ray() :
    A(0., 0., 0.),
    B(0., 0., 0.),
    tm(0.0)
{
}

ray::ray(const TrekMath::point3 &v0, const TrekMath::vec3 &b, double para_time) :
    A(v0), B(glm::normalize(b)), tm(para_time)
{
}

void ray::setOrigin(const TrekMath::point3 &p)
{
	A = p;
}

void ray::setDir(const TrekMath::vec3 &dir)
{
	B = glm::normalize(dir);
}

double ray::time() const
{
	return tm;
}

TrekMath::point3 ray::eye() const
{
	return A;
}

TrekMath::point3 ray::origin() const
{
	return A;
}

TrekMath::vec3 ray::direction() const
{
	return B;
}

TrekMath::vec3 ray::point_at_parameter(double t) const
{
	return A + t * B;
}
