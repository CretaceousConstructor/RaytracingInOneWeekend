#include "movingSphere.h"

movingSphere::movingSphere(TrekMath::point3 cen0, TrekMath::point3 cen1, double _time0, double _time1, double r, std::shared_ptr<material> m) :
    center0(cen0), center1(cen1), time0(_time0), time1(_time1), radius(r), mat_ptr(m)
{}

bool movingSphere::hit(const ray &r, double t_min, double t_max, shadeRec &sr) const
{
	TrekMath::vec3 oc = r.origin() - center(r.time());

	double a            = glm::length2(r.direction());
	double half_b       = glm::dot(oc, r.direction());
	double c            = glm::length2(oc) - radius * radius;
	double discriminant = half_b * half_b - a * c;

	if (discriminant >= 0.)
	{
		double sqare_root_of_disc = sqrt(discriminant);
		double temp               = (-half_b - sqare_root_of_disc) / a;        // temp is the parameter t,and is the one that's smaller between the two possible intersecting points,and it's closer
		if (temp <= t_max && temp >= t_min && (abs(temp) > kEpsilon))

		{
			sr.hitPoint = r.origin() + temp * r.direction();
			//调整法线使得视线方向和法线总是呈现钝角
			TrekMath::vec3 outward_normal = (sr.hitPoint - center(r.time())) / radius;        // intersecting normal vector,normalized
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
		if (temp <= t_max && temp >= t_min && (abs(temp) > kEpsilon))
		{
			sr.hitPoint                   = r.point_at_parameter(temp);
			TrekMath::vec3 outward_normal = (sr.hitPoint - center(r.time())) / radius;        // intersecting normal vector,normalized
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
bool movingSphere::shadow_hit(const ray &r, double &t_shadow) const
{
	return false;
}
bool movingSphere::bounding_box(double _time0, double _time1, AABB &output_box) const
{
	AABB box0(
	    center(_time0) - vec3(radius, radius, radius),
	    center(_time0) + vec3(radius, radius, radius));
	AABB box1(
	    center(_time1) - vec3(radius, radius, radius),
	    center(_time1) + vec3(radius, radius, radius));
	output_box = AABB::surrounding_box(box0, box1);
	return true;
};

std::string movingSphere::object_type() const
{
	return std::string("moving sphere");
}

TrekMath::point3 movingSphere::center(double time) const
{
	return center0 + ((time - time0) / (time1 - time0)) * (center1 - center0);
}
