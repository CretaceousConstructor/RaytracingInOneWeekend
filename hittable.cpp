#include "hittable.h"

hittable::hittable() :
	shadows(true)
{
}

hittable::hittable(std::shared_ptr<material> arg_mat_ptr)
	:
	shadows(true),
	mat_ptr(arg_mat_ptr)
{
}

bool hittable::bounding_box(double time0, double time1, AABB &output_box) const
{
	return false;
}

bool hittable::shadow_hit(const ray &r, double &t_shadow) const
{
	return false;
}

TrekMath::point3 hittable::sample()
{
	return TrekMath::point3();
}

TrekMath::normal hittable::get_normal(const TrekMath::point3 &p)
{
	return TrekMath::normal();
}

double hittable::pdf(shadeRec& sr) {
	return 1.0;
}
void hittable::set_shadows_object(bool arg_shadows)
{
	shadows = arg_shadows;
}
std::shared_ptr<material> hittable::get_mat_ptr() {
	return mat_ptr;
}
void hittable::set_material(std::shared_ptr<material> arg_mat)
{
	mat_ptr = arg_mat;
}
//bbox hittable::get_bounding_box() {
//	return bbox();
//}