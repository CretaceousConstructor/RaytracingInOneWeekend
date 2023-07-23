#pragma once
#include "TrekMath.h"

class Pdf
{
  public:
	Pdf()          = default;
	virtual ~Pdf() = default;

	[[nodiscard]] virtual double         Value(const TrekMath::vec3 &direction) const = 0;
	[[nodiscard]] virtual TrekMath::vec3 Generate() const                             = 0;
};
