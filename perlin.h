#pragma once
#include "TrekMath.h"
#include <vector>

class perlin
{
  public:
	perlin();
	double noise(const TrekMath::vec3 &p) const;

	float *ranfloat;
	int *  perm_x;
	int *  perm_y;
	int *  perm_z;
	//static float *ranfloat;
	//static int *  perm_x;
	//static int *  perm_y;
	//static int *  perm_z;
  private:
	static const int point_count = 256;

	std::vector<double> randreals;
	std::vector<int>    perm_x;
	std::vector<int>    perm_y;
	std::vector<int>    perm_z;

	static std::vector<int> perlin_generate_perm();

	static void permute(std::vector<int> p, int n);



};
