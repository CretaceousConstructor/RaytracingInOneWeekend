#pragma once
#include "ONB.h"
#include "Pdf.h"
class CosinePdfHemisphere : public Pdf
{
  public:
	//围绕w向量（通常是法向量）构建半球上的Cosine分布
	CosinePdfHemisphere(const TrekMath::vec3 &w);

	//给定一个半球上的向量，返回其在CosinePdf分布下生成的概率。
	[[nodiscard]] double Value(const TrekMath::vec3 &direction) const override;
	//生成在半球上符合CosinePdf分布的向量。
	[[nodiscard]] TrekMath::vec3 Generate() const override;

  private:
	static TrekMath::vec3 random_cosine_direction();

  public:
	ONB uvw{};
};
