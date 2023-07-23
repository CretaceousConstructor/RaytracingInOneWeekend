#pragma once
#include "Pdf.h"
#include "hittable.h"
#include <memory>
class HittablePdf : public Pdf
{
  public:
	//HittablePdf(std::shared_ptr<hittable> p, const TrekMath::point3 &origin);
	HittablePdf(const hittable &p, const TrekMath::point3 &origin);

	[[nodiscard]] double Value(const TrekMath::vec3 &direction) const override;

	[[nodiscard]] TrekMath::vec3 Generate() const override;

  public:
	TrekMath::point3 o;
	const hittable & objects;
};
