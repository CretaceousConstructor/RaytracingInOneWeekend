#include "sphere.h"


bool sphere::hit(const ray& r, double t_min, double t_max, shadeRec& sr) const {
	TrekMath::vec3 oc = r.eye() - center;
	auto a = glm::length2(r.direction());
	auto half_b = glm::dot(oc, r.direction());
	auto c = glm::length2(oc) - radius * radius;
	auto discriminant = half_b * half_b - a * c;

	if (discriminant > 0) {
		auto root = sqrt(discriminant);
		auto temp = (-half_b - root) / a;// temp is the parameter t,and is the one that's smaller between the two possible intersecting points,and it's closer
		if (temp <= t_max && temp >= t_min) {
			sr.hitPoint = r.eye() + temp * r.direction();
			//调整法线使得视线方向和法线总是呈现钝角
			TrekMath::vec3 outward_normal = (sr.hitPoint - center) / radius; // intersecting normal vector,normalized
			sr.set_face_normal(r, outward_normal);
			sr.hit_an_object = true;
			sr.mat_ptr = mat_ptr;
			sr.local_hitPoint = sr.hitPoint;//

			sr.cast_ray = r; //
			sr.t = temp;
			//sr.depth
			//sr.dir

			return true;
		}
		temp = (-half_b + root) / a;
		if (temp <= t_max && temp >= t_min) {
		
			sr.hitPoint = r.point_at_parameter(temp);
			TrekMath::vec3 outward_normal = (sr.hitPoint - center) / radius; // intersecting normal vector,normalized
			sr.set_face_normal(r, outward_normal);
			sr.hit_an_object = true;
			sr.mat_ptr = mat_ptr;
			sr.local_hitPoint = sr.hitPoint;//

			sr.cast_ray = r; //
			sr.t = temp;
			//sr.depth
			//sr.dir
			return true;
		}
	}
	return false;
}

bool sphere::shadow_hit(const ray& r, double& t_shadow) const
{
	if (!shadows) {
		return false;
	}
	else {

		TrekMath::vec3 oc = r.origin() - center;
		auto a = glm::length2(r.direction());
		auto half_b = glm::dot(oc, r.direction());
		auto c = glm::length2(oc) - radius * radius;
		auto discriminant = half_b * half_b - a * c;

		if (discriminant > 0) {
			auto root = sqrt(discriminant);
			auto temp = (-half_b - root) / a;// temp is the parameter t,and is the one that's smaller between the two possible intersecting points,and it's closer
			if (temp > kEpsilon) {
				t_shadow = temp;
				return true;
			}
			temp = (-half_b + root) / a;
			if (temp > kEpsilon) {
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

std::string sphere::objectType() const
{
	return std::string("sphere");
}
