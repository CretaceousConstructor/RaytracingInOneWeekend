#include "MixturePdf.h"

MixturePdf::MixturePdf(std::shared_ptr<Pdf> p0, std::shared_ptr<Pdf> p1)
{
	p[0] = p0;
	p[1] = p1;
}

double MixturePdf::Value(const TrekMath::vec3 &direction) const
{
	return 0.5 * p[0]->Value(direction) + 0.5 * p[1]->Value(direction);
}

TrekMath::vec3 MixturePdf::Generate() const
{
	if (TrekMath::random_double() < 0.5)
		return p[0]->Generate();
	else
		return p[1]->Generate();
}
