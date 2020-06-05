#pragma once
#include <math.h>
#include <stdlib.h>
#include <iostream>
class vec3
{
public:
	vec3() = default;
	vec3(double e0, double e1, double e2)
	{
		e[0] = e0;
		e[1] = e1;
		e[2] = e2;
	}
	inline double x()const { return e[0]; };
	inline double y()const { return e[1]; };
	inline double z()const { return e[2]; };
	inline double r()const { return e[0]; };
	inline double g()const { return e[1]; };
	inline double b()const { return e[2]; };
	inline const vec3& operator+() const {
		return *this;
	}
	inline  vec3 operator-() const {
		return vec3(-e[0], -e[1], -e[2]);
	}
	inline double operator[](int i) const {
		return e[i];
	}
	inline double& operator[](int i) {
		return e[i];
	}
	inline vec3& operator+=(const vec3& v2);
	inline vec3& operator-=(const vec3& v2);
	inline vec3& operator*=(const vec3& v2);
	inline vec3& operator/=(const vec3& v2);
	inline vec3& operator*=(const double t);
	inline vec3& operator/=(const double t);
	inline double length() const {
		return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
	}
	inline double squared_length() const {
		return (e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
	}
	inline void make_unit_vector();
	double e[3];

	static double dot(vec3 a, vec3 b) {
		return (a.e[0] * b.e[0] + a.e[1] * b.e[1] + a.e[2] * b.e[2]);
	}
	vec3& saturate() {
		if (e[0] > 1.0) { e[0] = 1.0; }
		if (e[1] > 1.0) { e[1] = 1.0; }
		if (e[2] > 1.0) { e[2] = 1.0; }
		return *this;
	}


	inline static vec3 random() {
		return vec3(random_double(), random_double(), random_double());
	}

	inline static vec3 random(double min, double max) {
		return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
	}


};





inline vec3 random_in_unit_sphere() {
	while (true) {
		auto p = vec3::random(-1, 1);
		if (p.squared_length() >= 1) continue;
		return p;
	}
}
vec3 random_unit_vector() {
	auto a = random_double(0, 2 * pi);
	auto z = random_double(-1, 1);
	auto r = sqrt(1 - z * z);
	//unit vector
	return vec3(r * cos(a), r * sin(a), z);
}

vec3 random_in_hemisphere(const vec3& normal) {
	vec3 in_unit_sphere = random_in_unit_sphere();
	if (vec3::dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
		return in_unit_sphere;
	else
		return -in_unit_sphere;
}


inline std::istream& operator>>(std::istream& is, vec3& t) {
	is >> t.e[0] >> t.e[1] >> t.e[2];
	return is;
}
inline std::ostream& operator<<(std::ostream& os, vec3& t) {
	os << t.e[0] << " " << t.e[1] << " " << t.e[2];
	return os;
}

inline vec3 operator+(const vec3& v1, const vec3& v2) {

	return vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}
inline vec3 operator-(const vec3& v1, const vec3& v2) {

	return vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}
inline vec3 operator*(const vec3& v1, const vec3& v2) {

	return vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}
inline vec3 operator/(const vec3& v1, const vec3& v2) {

	return vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}
inline vec3 operator*(double t, const vec3& v) {

	return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}
inline vec3 operator/(const vec3& v, double t) {

	return vec3(v.e[0] / t, v.e[1] / t, v.e[2] / t);
}
inline vec3 operator*(const vec3& v, float t) {

	return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}
inline vec3& vec3::operator+=(const vec3& v2)
{
	e[0] += v2.e[0];
	e[1] += v2.e[1];
	e[2] += v2.e[2];
	return *this;
}
inline vec3& vec3::operator-=(const vec3& v2)
{
	e[0] -= v2.e[0];
	e[1] -= v2.e[1];
	e[2] -= v2.e[2];
}
inline vec3& vec3::operator*=(const vec3& v2)
{
	e[0] *= v2.e[0];
	e[1] *= v2.e[1];
	e[2] *= v2.e[2];
}
inline vec3& vec3::operator/=(const vec3& v2)
{
	e[0] /= v2.e[0];
	e[1] /= v2.e[1];
	e[2] /= v2.e[2];
}
inline vec3& vec3::operator*=(const double t) {

	e[0] *= t;
	e[1] *= t;
	e[2] *= t;
	return *this;

}
inline vec3& vec3::operator/=(const double t) {

	double k = 1.0f / t;

	e[0] *= k;
	e[1] *= k;
	e[2] *= k;
	return *this;
}
inline void vec3::make_unit_vector()
{
	double k = 1.0f / sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
	e[0] *= k;
	e[1] *= k;
	e[2] *= k;

}
inline vec3 unit_vector(vec3 v) {
	return v / v.length();
}

vec3 reflect(const vec3& v, const vec3& n) {
	return v - 2 *vec3::dot(v, n) * n;
}

using point3 = vec3;   // 3D point
using color = vec3;    // RGB color