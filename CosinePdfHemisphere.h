#pragma once
#include "ONB.h"
#include "Pdf.h"
class CosinePdfHemisphere : public Pdf
{
  public:
	//Χ��w������ͨ���Ƿ����������������ϵ�Cosine�ֲ�
	CosinePdfHemisphere(const TrekMath::vec3 &w);

	//����һ�������ϵ���������������CosinePdf�ֲ������ɵĸ��ʡ�
	[[nodiscard]] double Value(const TrekMath::vec3 &direction) const override;
	//�����ڰ����Ϸ���CosinePdf�ֲ���������
	[[nodiscard]] TrekMath::vec3 Generate() const override;

  private:
	static TrekMath::vec3 random_cosine_direction();

  public:
	ONB uvw{};
};
