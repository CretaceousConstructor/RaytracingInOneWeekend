#pragma once
#include "TrekMath.h"
#include <vector>

class perlin
{
  public:
	perlin();
	double noise(const TrekMath::vec3 &p) const;
	double turb(const TrekMath::point3 &p, int depth = 7) const;

  private:
	std::vector<TrekMath::vec3> ranvecs;
	std::vector<double>         randreals;
	std::vector<int>            perm_x;
	std::vector<int>            perm_y;
	std::vector<int>            perm_z;

	static const int        point_count = 256;
	static std::vector<int> perlin_generate_perm();

	static void permute(std::vector<int> &p, int n);

	static double trilinear_interp(double c[2][2][2], double u, double v, double w);
	static double perlin_interp(TrekMath::vec3 c[2][2][2], double u, double v, double w);
};
