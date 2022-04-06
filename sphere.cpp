#include "sphere.h"

sphere::sphere(TrekMath::point3 cen, double r, std::shared_ptr<material> m)

    :
    hittable(m),
    center(cen),
    radius(r)
{
}

bool sphere::hit(const ray &r, double t_min, double t_max, shadeRec &sr) const
{
	TrekMath::vec3 oc           = r.origin() - center;
	double         a            = glm::length2(r.direction());
	double         half_b       = glm::dot(oc, r.direction());
	double         c            = glm::length2(oc) - radius * radius;
	double         discriminant = half_b * half_b - a * c;

	if (discriminant >= 0.)
	{
		double sqare_root_of_disc = sqrt(discriminant);
		double temp               = (-half_b - sqare_root_of_disc) / a;        // temp is the parameter t,and is the one that's smaller between the two possible intersecting points,and it's closer
		if (temp <= t_max && temp >= t_min)
		{
			sr.hitPoint = r.origin() + temp * r.direction();
			//调整法线使得视线方向和法线总是呈现钝角
			TrekMath::vec3 outward_normal = (sr.hitPoint - center) / radius;        // intersecting normal vector,normalized
			sr.set_front_face_and_normal(r, outward_normal);
			sr.hit_an_object = true;
			sr.mat_ptr       = mat_ptr;

			sr.local_hitPoint = sr.hitPoint;        //
			sr.cast_ray       = r;                  //
			sr.t              = temp;

			//sr.depth
			//sr.dir

			return true;
		}

		temp = (-half_b + sqare_root_of_disc) / a;
		if (temp <= t_max && temp >= t_min)
		{
			sr.hitPoint                   = r.point_at_parameter(temp);
			TrekMath::vec3 outward_normal = (sr.hitPoint - center) / radius;        // intersecting normal vector,normalized
			sr.set_front_face_and_normal(r, outward_normal);
			sr.hit_an_object  = true;
			sr.mat_ptr        = mat_ptr;
			sr.local_hitPoint = sr.hitPoint;        //

			sr.cast_ray = r;        //
			sr.t        = temp;
			//sr.depth
			//sr.dir
			return true;
		}
	}

	return false;
}

bool sphere::shadow_hit(const ray &r, double &t_shadow) const
{
	if (!shadows)
	{
		return false;
	}
	else
	{
		TrekMath::vec3 oc           = r.origin() - center;
		auto           a            = glm::length2(r.direction());
		auto           half_b       = glm::dot(oc, r.direction());
		auto           c            = glm::length2(oc) - radius * radius;
		auto           discriminant = half_b * half_b - a * c;

		if (discriminant > 0)
		{
			auto root = sqrt(discriminant);
			auto temp = (-half_b - root) / a;        // temp is the parameter t,and is the one that's smaller between the two possible intersecting points,and it's closer
			if (temp > kEpsilon)
			{
				t_shadow = temp;
				return true;
			}
			temp = (-half_b + root) / a;
			if (temp > kEpsilon)
			{
				t_shadow = temp;
				return true;
			}
		}
		else
		{
			return false;
		}

		return false;
	}
}

bool sphere::bounding_box(double time0, double time1, AABB &output_box) const

{


    output_box = AABB(
        center - vec3(radius, radius, radius),
        center + vec3(radius, radius, radius));
    return true;


}

std::string sphere::objectType() const
{
	return std::string("sphere");
}
