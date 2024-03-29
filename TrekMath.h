#pragma once

#define GLM_FORCE_RADIANS
#include <GLFW/glfw3.h>
#include <array>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <limits>
#include <random>

namespace TrekMath
{
//variables
/*std::random_device rd;
	std::mt19937 generator(rd());*/

extern std::mt19937 generator;        //random number generator

//Name aliasing
using real = double;

using mat4 = glm::dmat4;        //4*4 matrix
using vec4 = glm::dvec4;        //4D vector
using vec3 = glm::dvec3;        //3D vector
using vec2 = glm::dvec2;        //2D vector
//====================================================================================
using point4 = vec4;        // 3D point
using point3 = vec3;        // 3D point
using point2 = vec2;        // 2D point
using color  = vec3;        // RGB color
using normal = vec3;        // normal

struct texcoor2d
{
	real u, v;
};




//Constants
constexpr real infinity     = std::numeric_limits<real>::infinity();
constexpr real epsilon      = 0.00001;
constexpr real small_number = 0.00001;

constexpr real PI = glm::pi<real>();



//Funcions
int    random_int(int min, int max);                                       //Produces random integer values i , uniformly distributed on the closed interval [min, max] ,
double random_double(double min = 0.0, double max = 1.0);                  // Returns a random real number in [min,max).
double random_double_inclusive(double min = 0.0, double max = 1.0);        // Returns a random real number in [min,max].

vec3 random(double min, double max);                  //a vec3 with three components randomly distributed over [min,max).
vec3 random_inclusive(double min, double max);        //a vec3 with three components randomly distributed over [min,max].
vec3 random_unit_vector();                            //a vec3 with three components randomly distributed and of lenth 1.0

vec3 random_within_unit_sphere();

//generate vec3 on hemisphere with a pdf of (cos(��) / pi);
vec3 random_cosine_direction();


bool near_zero(vec3 e);

double clamp(double x, double min, double max);

vec3 reflect(const vec3 &v, const vec3 &n);
vec3 refract(const vec3 &uv, const vec3 &n, double etai_over_etat);

double degrees_to_radians(double degrees);

int  solveQuartic(double c[5], double s[4]);
int  solveQuadric(double c[3], double s[2]);
int  solveCubic(double c[4], double s[3]);
bool isZero(double r);

point3 transform_point3(const glm::mat4x4 &m, const point3 &p);

vec3 transform_vec3(const glm::mat4x4 &m, const vec3 &p);

}        // namespace TrekMath