#include "torus.h"

bool torus::hit(const ray& r, double t_min, double t_max, shadeRec& sr) const
{


	double x1 = r.origin().x;
	double y1 = r.origin().y;
	double z1 = r.origin().z;
	double d1 = r.direction().x;
	double d2 = r.direction().y;
	double d3 = r.direction().z;

	double coeffs[5];	// coefficient array for the quartic equation
	double roots[4];	// solution array for the quartic equation

	// define the coefficients of the quartic equation

	double sum_d_sqrd = d1 * d1 + d2 * d2 + d3 * d3;
	double e = x1 * x1 + y1 * y1 + z1 * z1 - a * a - b * b;
	double f = x1 * d1 + y1 * d2 + z1 * d3;
	double four_a_sqrd = 4.0 * a * a;

	coeffs[0] = e * e - four_a_sqrd * (b * b - y1 * y1); 	// constant term
	coeffs[1] = 4.0 * f * e + 2.0 * four_a_sqrd * y1 * d2;
	coeffs[2] = 2.0 * sum_d_sqrd * e + 4.0 * f * f + four_a_sqrd * d2 * d2;
	coeffs[3] = 4.0 * sum_d_sqrd * f;
	coeffs[4] = sum_d_sqrd * sum_d_sqrd;  					// coefficient of t^4

	// find roots of the quartic equation

	int num_real_roots = TrekMath::solveQuartic(coeffs, roots);

	bool	intersected = false;
	double 	t = TrekMath::infinity;

	if (num_real_roots == 0)  // ray misses the torus
		return(false);

	// find the smallest root greater than kEpsilon, if any
	// the roots array is not sorted

	for (int j = 0; j < num_real_roots; j++)
		if (roots[j] > kEpsilon) {
			intersected = true;
			if (roots[j] < t) {

				t = roots[j];
			}
		}

	if (!intersected) {

		return (false);
	}

	sr.t = t;
	sr.hitPoint = r.point_at_parameter(t);
	sr.local_hitPoint = r.point_at_parameter(t);
	//sr.set_front_face_and_normal(r, compute_normal(sr.hitPoint));
	sr.normal = compute_normal(sr.hitPoint);
	sr.cast_ray = r;
	sr.hit_an_object = true;
	sr.mat_ptr = mat_ptr;


	return (true);
}

std::string torus::objectType() const
{
	return std::string("torus");
}

torus::torus(const double _a, const double _b, std::shared_ptr<material> m)
	: hittable(m),
	a(_a),
	b(_b)
{}

bool torus::shadow_hit(const ray& r, double& t_shadow) const
{

	double x1 = r.origin().x;
	double y1 = r.origin().y;
	double z1 = r.origin().z;
	double d1 = r.direction().x;
	double d2 = r.direction().y;
	double d3 = r.direction().z;

	double coeffs[5];	// coefficient array for the quartic equation
	double roots[4];	// solution array for the quartic equation

	// define the coefficients of the quartic equation

	double sum_d_sqrd = d1 * d1 + d2 * d2 + d3 * d3;
	double e = x1 * x1 + y1 * y1 + z1 * z1 - a * a - b * b;
	double f = x1 * d1 + y1 * d2 + z1 * d3;
	double four_a_sqrd = 4.0 * a * a;

	coeffs[0] = e * e - four_a_sqrd * (b * b - y1 * y1); 	// constant term
	coeffs[1] = 4.0 * f * e + 2.0 * four_a_sqrd * y1 * d2;
	coeffs[2] = 2.0 * sum_d_sqrd * e + 4.0 * f * f + four_a_sqrd * d2 * d2;
	coeffs[3] = 4.0 * sum_d_sqrd * f;
	coeffs[4] = sum_d_sqrd * sum_d_sqrd;  					// coefficient of t^4

	// find roots of the quartic equation

	int num_real_roots = TrekMath::solveQuartic(coeffs, roots);

	bool	intersected = false;
	double 	t = TrekMath::infinity;

	if (num_real_roots == 0)  // ray misses the torus
		return(false);

	// find the smallest root greater than kEpsilon, if any
	// the roots array is not sorted

	for (int j = 0; j < num_real_roots; j++)
		if (roots[j] > kEpsilon) {
			intersected = true;
			if (roots[j] < t) {

				t = roots[j];
			}
		}

	if (!intersected) {

		return (false);
	}

	if (t < kEpsilon) {
		return false;
	}

	t_shadow = t;

	return (true);
}


TrekMath::normal torus::compute_normal(const TrekMath::point3& p) const
{
	TrekMath::normal normal;
	double param_squared = a * a + b * b;

	double x = p.x;
	double y = p.y;
	double z = p.z;
	double sum_squared = x * x + y * y + z * z;

	normal.x = 4.0 * x * (sum_squared - param_squared);
	normal.y = 4.0 * y * (sum_squared - param_squared + 2.0 * a * a);
	normal.z = 4.0 * z * (sum_squared - param_squared);

	return glm::normalize(normal); //don't forget to normalize;
}
