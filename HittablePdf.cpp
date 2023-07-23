#include "HittablePdf.h"

//HittablePdf::HittablePdf(std::shared_ptr<hittable> p, const TrekMath::point3 &origin) :
//    o(origin), ptr(p)
//{}

HittablePdf::HittablePdf(const hittable &p, const TrekMath::point3 &origin) :
    o(origin),
    objects(p)
{}

double HittablePdf::Value(const TrekMath::vec3 &direction) const
{
	return objects.PdfValue(o, direction);
}

TrekMath::vec3 HittablePdf::Generate() const
{
	return objects.Random(o);
}
