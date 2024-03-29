#include "plane.h"

plane::plane(TrekMath::point3 p, TrekMath::vec3 normalOfPlane, std::shared_ptr<material> m)

	:
	hittable(m),
	arbitraryPoint(p), normal(glm::normalize(normalOfPlane)){

};

bool plane::hit(const ray& r, double t_min, double t_max, shadeRec& sr) const {

	
	auto t = glm::dot((arbitraryPoint - r.origin()), normal) / (glm::dot(r.direction(), normal));

	if (t > t_min && t < t_max) {
		sr.hitPoint = r.point_at_parameter(t);
		sr.set_front_face_and_normal(r,normal);
		sr.hit_an_object = true;
		sr.mat_ptr = mat_ptr;
		sr.local_hitPoint = r.point_at_parameter(t);//
		sr.cast_ray = r; //
		sr.t = t;
		
		//sr.front_face = glm::dot((sr.hitPoint - r.eye()), normal) < 0.;
		//sr.depth
		//sr.dir
		return true;
	}
	else
	{
		return false;
	}

}

bool plane::shadow_hit(const ray& r, double& t_shadow) const
{

	if (!shadows) {
		return false;
	}
	else {

		double t = glm::dot((arbitraryPoint - r.eye()), normal) / (glm::dot(r.direction(), normal));

		if (abs(t) > kEpsilon) {

			t_shadow = t;
			return true;
		}
		else {
			return false;
		}

	}


}

std::string plane::object_type() const
{
	return std::string("plane");
}

