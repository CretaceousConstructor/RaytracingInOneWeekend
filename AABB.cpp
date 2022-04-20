#include "AABB.h"


AABB::AABB(const TrekMath::point3 &a, const TrekMath::point3 &b) :
    minimum(a), maximum(b)
{
}

bool AABB::hit(const ray &r_in, double t_min, double t_max, shadeRec &sr) const
{
	ray temp_ray = r_in;


	for (int a = 0; a < 3; a++)
	{
		auto invD = 1.0f / temp_ray.direction()[a];
		auto t0   = (min()[a] - temp_ray.origin()[a]) * invD;
		auto t1   = (max()[a] - temp_ray.origin()[a]) * invD;
		if (invD < 0.0f)
		{
			std::swap(t0, t1);
		}
		t_min = t0 > t_min ? t0 : t_min;
		t_max = t1 < t_max ? t1 : t_max;
		if (t_max <= t_min)
		{
			return false;
		}
	}

	return true;



}

std::string AABB::objectType() const
{
	return std::string("axis aligned bounding box");
}

TrekMath::point3 AABB::min() const
{
	return minimum;
}

TrekMath::point3 AABB::max() const
{
	return maximum;
}


AABB AABB::surrounding_box(const AABB& box0,const AABB& box1)
{






	TrekMath::point3 small(fmin(box0.min().x, box1.min().x),
	                       fmin(box0.min().y, box1.min().y),
	                       fmin(box0.min().z, box1.min().z));

	TrekMath::point3 big(fmax(box0.max().x, box1.max().x),
	                     fmax(box0.max().y, box1.max().y),
	                     fmax(box0.max().z, box1.max().z));

	return AABB(small, big);





}
