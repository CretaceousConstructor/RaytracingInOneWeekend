#include "TrekMath.h"

namespace TrekMath {
	double random_double(double min, double max) {// Returns a random real in [min,max].

		//std::random_device rd;
		//std::mt19937 e2(rd());
		//static std::mt19937 generator;

		//static std::uniform_real_distribution<double> distribution(min, max); //// Returns a random real in [min,max)
		std::uniform_real_distribution<double> distribution(min, std::nextafter(max, DBL_MAX)); //TO DO optimizition

		return distribution(generator);
	}
	vec3 random(double min, double max) {
		return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
	}
	

	



	vec3 reflect(const vec3& v, const vec3& sqrt_of_numSamples) {
		return v - 2 * glm::dot(v, sqrt_of_numSamples) * sqrt_of_numSamples;
	}
	vec3 refract(const vec3& uv, const vec3& sqrt_of_numSamples, double etai_over_etat) {
		auto cos_theta = glm::dot(-uv, sqrt_of_numSamples);
		vec3 r_out_parallel = etai_over_etat * (uv + cos_theta * sqrt_of_numSamples);
		vec3 r_out_perp = -sqrt(1.0 - glm::length2(r_out_parallel)) * sqrt_of_numSamples;
		return r_out_parallel + r_out_perp;
	}
	double degrees_to_radians(double degrees) {
		return glm::radians(degrees);
	}
	double clamp(double x, double min, double max) { //Returns min(max(x, minVal), maxVal)
		return glm::clamp(x, min, max);
	}

	vec3 random_unit_vector() { //长度严格为1的向量
		auto a = random_double(0, 2.0 * glm::pi<double>());
		auto z = random_double(-1, 1);
		auto r = glm::sqrt(1 - z * z);
		return vec3(r * glm::cos(a), r * glm::sin(a), z);
	}
}