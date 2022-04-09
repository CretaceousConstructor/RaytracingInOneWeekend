#pragma once

#define GLM_FORCE_RADIANS
#include <GLFW/glfw3.h>
#include <array>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <limits>
#include <random>
#include <stdlib.h>

namespace TrekMath
{
//variables
/*std::random_device rd;
	std::mt19937 generator(rd());*/

extern std::mt19937 generator;        //random number generator

//Name aliasing
using real = double;
using vec3 = glm::dvec3;        //3D vector
using vec2 = glm::dvec2;        //2D vector

using point3 = vec3;        // 3D point
using point2 = vec2;        // 2D point
using color  = vec3;        // RGB color
using normal = vec3;        // normal

struct texcoor2d
{
	real u, v;
};

//Constants
constexpr double infinity     = std::numeric_limits<double>::infinity();
constexpr double epsilon      = 0.00001;
constexpr double small_number = 0.00001;

//Funcions

int random_int(int min, int max);        //Produces random integer values i , uniformly distributed on the closed interval [min, max] ,

double random_double(double min = 0.0, double max = 1.0);                  // Returns a random real number in [min,max).
double random_double_inclusive(double min = 0.0, double max = 1.0);        // Returns a random real number in [min,max].


vec3 random(double min, double max);                  //a vec3 with three components randomly distributed over [min,max).
vec3 random_inclusive(double min, double max);        //a vec3 with three components randomly distributed over [min,max].

vec3 random_unit_vector();        //a vec3 with three components randomly distributed and of lenth 1.0

vec3 random_in_unit_sphere();

bool near_zero(vec3 &e);

double clamp(double x, double min, double max);

vec3 reflect(const vec3 &v, const vec3 &n);
vec3 refract(const vec3 &uv, const vec3 &n, double etai_over_etat);

double degrees_to_radians(double degrees);

int  solveQuartic(double c[5], double s[4]);
int  solveQuadric(double c[3], double s[2]);
int  solveCubic(double c[4], double s[3]);
bool isZero(double r);

}        // namespace TrekMath