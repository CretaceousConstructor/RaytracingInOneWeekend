#include "perlin.h"

perlin::perlin()
{
	randreals.resize(point_count);
	for (auto itr = randreals.begin(); itr != randreals.end(); itr++)
	{
		*itr = TrekMath::random_double();
	}
	perm_x = perlin_generate_perm();
	perm_y = perlin_generate_perm();
	perm_z = perlin_generate_perm();
}

double perlin::noise(const TrekMath::vec3 &p) const
{
	int i = int(4 * p.x) & 255;
	int j = int(4 * p.y) & 255;
	int k = int(4 * p.z) & 255;
	return ranfloat[perm_x[i] ^ perm_y[j] ^ perm_z[k]];
}

std::vector<int> perlin::perlin_generate_perm()
{
	std::vector<int> p(point_count);

	for (int i = 0; i < perlin::point_count; i++)
	{
		p[i] = i;
	}

	permute(p, point_count);

	return p;
}

void perlin::permute(std::vector<int> p, int n)
{
	for (int i = n - 1; i > 0; i--)
	{
		int target = TrekMath::random_int(0, i);
		int tmp    = p[i];
		p[i]       = p[target];
		p[target]  = tmp;
	}
}
