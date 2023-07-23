#pragma once
#include "Pdf.h"
#include <array>
#include <memory>

class MixturePdf : public Pdf
{
  public:
	MixturePdf(std::shared_ptr<Pdf> p0, std::shared_ptr<Pdf> p1);
	MixturePdf() = delete;

	[[nodiscard]] double         Value(const TrekMath::vec3 &direction) const override;
	[[nodiscard]] TrekMath::vec3 Generate() const override;

  public:
	std::array<std::shared_ptr<Pdf>, 2> p;
};
