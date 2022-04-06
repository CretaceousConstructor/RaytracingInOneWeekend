#include "triangle.h"

triangle::triangle(TrekMath::point3 arg_a, TrekMath::point3 arg_b, TrekMath::point3 arg_c, std::shared_ptr<material> arg_mat)
	:
	hittable(arg_mat),
	v0(arg_a),
	v1(arg_b),
	v2(arg_c)
{
	nor = glm::normalize(glm::cross((v1 - v0), (v2 - v0)));

}

bool triangle::hit(const ray& r, double t_min, double t_max, shadeRec& sr) const
{
	double a = v0.x - v1.x, b = v0.x - v2.x, c = r.direction().x, d = v0.x - r.origin().x;
	double e = v0.y - v1.y, f = v0.y - v2.y, g = r.direction().y, h = v0.y - r.origin().y;
	double i = v0.z - v1.z, j = v0.z - v2.z, k = r.direction().z, l = v0.z - r.origin().z;

	double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
	double q = g * i - e * k, s = e * j - f * i;

	double inv_denom = 1.0 / (a * m + b * q + c * s);

	double e1 = d * m - b * n - c * p;
	double beta = e1 * inv_denom;

	if (beta < 0.0)
		return (false);

	double valuer = valuer = e * l - h * i;
	double e2 = a * n + d * q + c * valuer;
	double gamma = e2 * inv_denom;

	if (gamma < 0.0)
		return (false);

	if (beta + gamma > 1.0)
		return (false);

	double e3 = a * p - b * valuer + d * s;
	double t = e3 * inv_denom;

	if (t < kEpsilon || t < t_min || t > t_max) {

		return (false);
	}
	sr.set_front_face_and_normal(r, nor);
	sr.mat_ptr = mat_ptr;
	sr.t = t;
	sr.normal = nor;
	sr.hitPoint = r.point_at_parameter(t);
	sr.local_hitPoint = sr.hitPoint;

	return (true);
}

std::string triangle::objectType() const
{
	return std::string("triangle");
}

bool triangle::shadow_hit(const ray& r, double& t_shadow) const
{

	if (!shadows) {
		return false;
	}
	double a = v0.x - v1.x, b = v0.x - v2.x, c = r.direction().x, d = v0.x - r.origin().x;
	double e = v0.y - v1.y, f = v0.y - v2.y, g = r.direction().y, h = v0.y - r.origin().y;
	double i = v0.z - v1.z, j = v0.z - v2.z, k = r.direction().z, l = v0.z - r.origin().z;

	double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
	double q = g * i - e * k, s = e * j - f * i;

	double inv_denom = 1.0 / (a * m + b * q + c * s);

	double e1 = d * m - b * n - c * p;
	double beta = e1 * inv_denom;

	if (beta < 0.0)
		return (false);

	double valuer = valuer = e * l - h * i;
	double e2 = a * n + d * q + c * valuer;
	double gamma = e2 * inv_denom;

	if (gamma < 0.0)
		return (false);

	if (beta + gamma > 1.0)
		return (false);

	double e3 = a * p - b * valuer + d * s;
	double t = e3 * inv_denom;

	if (t < kEpsilon) {
		return false;
	}
	else {
		t_shadow = t;
		return true;
	}

}
