#pragma once

#define GLM_FORCE_RADIANS
#include <limits>
#include <stdlib.h>
#include <random>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/norm.hpp>


namespace TrekMath
{


	//vars
	/*std::random_device rd;
	std::mt19937 generator(rd());*/
	static std::mt19937 generator(12);
	//name aliasing
	using vec3 = glm::dvec3;
	using vec2 = glm::dvec2;

	using point3 = vec3;    // 3D point
	using point2 = vec2;
	using color = vec3;    // RGB color
	using normal = vec3;
	//const 
	const double infinity = std::numeric_limits<double>::infinity();
	const double epsilon = 0.;
	//func
	double random_double(double min = 0.0, double max = 1.0);// Returns a random real in [min,max].
	vec3 random(double min, double max);  //a vec3 with three components randomly distributed over [min,max]
	double clamp(double x, double min, double max);

	vec3 reflect(const vec3& v, const vec3& sqrt_of_numSamples);
	vec3 refract(const vec3& uv, const vec3& sqrt_of_numSamples, double etai_over_etat);
	double degrees_to_radians(double degrees);
	vec3 random_unit_vector();
	


}