#include "rectangle.h"

bool rectangle::hit(const ray& r, double t_min, double t_max, shadeRec& sr) const
{
	double t = glm::dot((p0 - r.origin()), normal) / glm::dot(r.direction(), normal);
	if (t <= kEpsilon || t < t_min || t > t_max)
	{
		return false;

	}
	TrekMath::point3 p = r.point_at_parameter(t);
	TrekMath::vec3 d = p - p0;
	double dDota = glm::dot(d, a);
	if (dDota < 0. || dDota > glm::length2(a)) {
		return false;
	}
	double dDotb = glm::dot(d, b);
	if (dDotb < 0. || dDotb > glm::length2(b)) {
		return false;
	}


	sr.hitPoint = p;
	sr.normal = normal;
	sr.hit_an_object = true;
	sr.local_hitPoint = sr.hitPoint;//
	sr.mat_ptr = mat_ptr;
	sr.cast_ray = r; //
	sr.t = t;
	//sr.depth
	//sr.dir

	return true;


}

std::string rectangle::objectType() const
{
	return std::string("rectangle");
}

TrekMath::point3 rectangle::sample()
{
	TrekMath::point2 sample_point = sampler_ptr->sample_unit_square();

	return (p0 + sample_point.x *a + sample_point.y*b);
}

double rectangle::pdf(shadeRec& sr)
{
	return inv_area;
}
TrekMath::normal rectangle::get_normal(const TrekMath::point3& p)
{
	return normal;
}

void rectangle::set_sampler(std::unique_ptr<sampler>&& arg_sam)
{
	sampler_ptr = std::move(arg_sam);
	
}

