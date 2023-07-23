#include "CosinePdfHemisphere.h"

CosinePdfHemisphere::CosinePdfHemisphere(const TrekMath::vec3 &w)
{
	uvw.BuildFromW(w);
}

double CosinePdfHemisphere::Value(const TrekMath::vec3 &direction) const
{
	//direction是任意方向，uvw.w()是法线方向，返回的值表示当前pdf采样到direction的概率
	const auto cosine = glm::dot(glm::normalize(direction), uvw.w());
	return (cosine <= 0) ? 0 : cosine / TrekMath::PI;
}

TrekMath::vec3 CosinePdfHemisphere::Generate() const
{ 
	return uvw.LocalCoordToAbsoluteWorldCoord(random_cosine_direction());
}

TrekMath::vec3 CosinePdfHemisphere::random_cosine_direction()
{
	const auto r1 = TrekMath::random_double_inclusive();
	const auto r2 = TrekMath::random_double_inclusive();
	const auto z  = sqrt(1 - r2);

	const auto phi = 2 * TrekMath::PI * r1;
	const auto x   = cos(phi) * sqrt(r2);
	const auto y   = sin(phi) * sqrt(r2);

	return {x, y, z};
}
