#include "TrekMath.h"

namespace TrekMath
{
double random_double(double min, double max)
{        // Returns a random real in [min,max)

	//std::random_device rd;
	//std::mt19937 e2(rd());
	//static std::mt19937 generator;
	//std::uniform_real_distribution<double> distribution(min, max); //// Returns a random real in [min,max)

	const std::uniform_real_distribution<double> distribution(min, max);        //TO DO optimizition
	return distribution(generator);
}
double random_double_inclusive(double min, double max)
{
	//std::uniform_real_distribution<double> distribution(min, max); //// Returns a random real in [min,max)
	const std::uniform_real_distribution<double> distribution(min, std::nextafter(max, DBL_MAX));        //TO DO optimizition
	return distribution(generator);
}
int random_int(int min, int max)
{
	//Produces random integer values i , uniformly distributed on the closed interval [ a , b ] ,
	std::uniform_int_distribution<> distribution(min, max);        //TO DO optimizition
	return distribution(generator);
}
vec3 random(double min, double max)
{
	return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
}

vec3 random_inclusive(double min, double max)
{
	return vec3(random_double_inclusive(min, max), random_double_inclusive(min, max), random_double_inclusive(min, max));
}

vec3 reflect(const vec3 &v, const vec3 &n)
{
	return v - 2 * glm::dot(v, n) * n;
}
vec3 refract(const vec3 &uv, const vec3 &n, double etai_over_etat)
{
	const auto cos_theta      = glm::dot(-uv, n);
	const vec3 r_out_perp     = etai_over_etat * (uv + cos_theta * n);
	const vec3 r_out_parallel = -sqrt(1.0 - glm::length2(r_out_perp)) * n;
	return r_out_parallel + r_out_perp;
}
double degrees_to_radians(double degrees)
{
	return glm::radians(degrees);
}

bool near_zero(vec3 e)
{
	// Return true if the vector is close to zero in all dimensions.
	constexpr auto s = 1e-8;
	return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
}

double clamp(double x, double min, double max)
{        //Returns min(max(x, minVal), maxVal)
	return glm::clamp(x, min, max);
}

vec3 random_unit_vector()
{
	const auto a = random_double(0, 2.0 * glm::pi<double>());
	const auto z = random_double(-1, 1);
	const auto r = glm::sqrt(1 - z * z);
	return TrekMath::vec3(r * glm::cos(a), r * glm::sin(a), z);
}

vec3 random_within_unit_sphere()
{
	while (true)
	{
		auto p = random(-1., 1.);
		if (glm::length2(p) >= 1.)
		{
			continue;
		}
		return p;
	}
}




int solveQuadric(double c[3], double s[2])
{
	double p, q, D;

	/* normal form: x^2 + px + q = 0 */

	p = c[1] / (2 * c[2]);
	q = c[0] / c[2];

	D = p * p - q;

	if (isZero(D))
	{
		s[0] = -p;
		return 1;
	}
	else if (D > 0)
	{
		double sqrt_D = sqrt(D);

		s[0] = sqrt_D - p;
		s[1] = -sqrt_D - p;
		return 2;
	}
	else /* if (D < 0) */
		return 0;
}

int solveCubic(double c[4], double s[3])
{
	int    i, num;
	double sub;
	double A, B, C;
	double sq_A, p, q;
	double cb_p, D;

	/* normal form: x^3 + Ax^2 + Bx + C = 0 */

	A = c[2] / c[3];
	B = c[1] / c[3];
	C = c[0] / c[3];

	/*  substitute x = y - A/3 to eliminate quadric term:
        x^3 +px + q = 0 */

	sq_A = A * A;
	p    = 1.0 / 3 * (-1.0 / 3 * sq_A + B);
	q    = 1.0 / 2 * (2.0 / 27 * A * sq_A - 1.0 / 3 * A * B + C);

	/* use Cardano's formula */

	cb_p = p * p * p;
	D    = q * q + cb_p;

	if (isZero(D))
	{
		if (isZero(q))
		{ /* one triple solution */
			s[0] = 0;
			num  = 1;
		}
		else
		{ /* one single and one double solution */
			double u = cbrt(-q);
			s[0]     = 2 * u;
			s[1]     = -u;
			num      = 2;
		}
	}
	else if (D < 0)
	{ /* Casus irreducibilis: three real solutions */
		double phi = 1.0 / 3 * acos(-q / sqrt(-cb_p));
		double t   = 2 * sqrt(-p);

		s[0] = t * cos(phi);
		s[1] = -t * cos(phi + glm::pi<double>() / 3);
		s[2] = -t * cos(phi - glm::pi<double>() / 3);
		num  = 3;
	}
	else
	{ /* one real solution */
		double sqrt_D = sqrt(D);
		double u      = cbrt(sqrt_D - q);
		double v      = -cbrt(sqrt_D + q);

		s[0] = u + v;
		num  = 1;
	}

	/* resubstitute */

	sub = 1.0 / 3 * A;

	for (i = 0; i < num; ++i)
		s[i] -= sub;

	return num;
}

int solveQuartic(double c[5], double s[4])
{
	double coeffs[4];
	double z, u, v, sub;
	double A, B, C, D;
	double sq_A, p, q, r;
	int    i, num;

	/* normal form: x^4 + Ax^3 + Bx^2 + Cx + D = 0 */

	A = c[3] / c[4];
	B = c[2] / c[4];
	C = c[1] / c[4];
	D = c[0] / c[4];

	/*  substitute x = y - A/4 to eliminate cubic term:
        x^4 + px^2 + qx + r = 0 */

	sq_A = A * A;
	p    = -3.0 / 8 * sq_A + B;
	q    = 1.0 / 8 * sq_A * A - 1.0 / 2 * A * B + C;
	r    = -3.0 / 256 * sq_A * sq_A + 1.0 / 16 * sq_A * B - 1.0 / 4 * A * C + D;

	if (isZero(r))
	{
		/* no absolute term: y(y^3 + py + q) = 0 */

		coeffs[0] = q;
		coeffs[1] = p;
		coeffs[2] = 0;
		coeffs[3] = 1;

		num = solveCubic(coeffs, s);

		s[num++] = 0;
	}
	else
	{
		/* solve the resolvent cubic ... */

		coeffs[0] = 1.0 / 2 * r * p - 1.0 / 8 * q * q;
		coeffs[1] = -r;
		coeffs[2] = -1.0 / 2 * p;
		coeffs[3] = 1;

		solveCubic(coeffs, s);

		/* ... and take the one real solution ... */

		z = s[0];

		/* ... to build two quadric equations */

		u = z * z - r;
		v = 2 * z - p;

		if (isZero(u))
			u = 0;
		else if (u > 0)
			u = sqrt(u);
		else
			return 0;

		if (isZero(v))
			v = 0;
		else if (v > 0)
			v = sqrt(v);
		else
			return 0;

		coeffs[0] = z - u;
		coeffs[1] = q < 0 ? -v : v;
		coeffs[2] = 1;

		num = solveQuadric(coeffs, s);

		coeffs[0] = z + u;
		coeffs[1] = q < 0 ? v : -v;
		coeffs[2] = 1;

		num += solveQuadric(coeffs, s + num);
	}

	/* resubstitute */

	sub = 1.0 / 4 * A;

	for (i = 0; i < num; ++i)
		s[i] -= sub;

	return num;
}

bool isZero(double r)
{
	return glm::abs(r) < small_number;
}

point3 transform_point3(const glm::mat4x4 &m, const point3 &p)
{
	return point3(m * point4(p, 1.0));
}

vec3 transform_vec3(const glm::mat4x4 &m, const vec3 &p)
{
	return vec3(m * vec4(p, 0.0));
}

}        // namespace TrekMath