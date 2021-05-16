#include "shadeRec.h"

 void shadeRec::set_face_normal(const ray& r, const TrekMath::vec3& outward_normal)
{

	//front_face = glm::dot(r.direction(), outward_normal) < 0;
	front_face = glm::dot(r.direction(), outward_normal) < 0;


	normal = front_face ? outward_normal : -outward_normal;
}
