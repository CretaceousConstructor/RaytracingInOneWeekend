#include "shadeRec.h"

void shadeRec::set_front_face_and_normal(const ray &r, const TrekMath::vec3 &outward_normal)
{
	front_face = glm::dot(r.direction(), outward_normal) < 0.;

	normal = front_face ? outward_normal : -outward_normal;
}

shadeRec::shadeRec(const MultipleObj &w) :
    hit_an_object(false),
    mat_ptr(nullptr),
    depth(0),
    wor(&w)
{
}
