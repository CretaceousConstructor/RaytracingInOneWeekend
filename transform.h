#pragma once
#include "TrekMath.h"

class transform
{
  public:
	transform(const TrekMath::vec3 &scale, const TrekMath::vec3 &rotation, const TrekMath::vec3 &position);
	transform()  = default;
	~transform() = default;

	transform(const transform &) = default;
	transform &operator=(const transform &) = default;

	transform(transform &&) = default;
	transform &operator=(transform &&) = default;

	// ��ȡ�������ű���
	TrekMath::vec3 GetScale() const;

	// ��ȡ����ŷ����(������)
	// ������Y-X-Z��˳����ת?�Ƿ���������Ҫ����
	TrekMath::vec3 GetRotation() const;

	// ��ȡ����λ��
	TrekMath::vec3 GetPosition() const;

	// ��ȡ�ҷ�����
	TrekMath::vec3 GetRightAxis() const;

	// ��ȡ�Ϸ�����
	TrekMath::vec3 GetUpAxis() const;

	// ��ȡǰ������
	TrekMath::vec3 GetForwardAxis() const;

	// ��ȡ����任����
	TrekMath::mat4 GetLocalToWorldMatrix() const;

	// ��ȡ������任����
	TrekMath::mat4 GetWorldToLocalMatrix() const;

	// ���ö������ű���
	void SetScale(const TrekMath::vec3 &scale);
	// ���ö������ű���
	void SetScale(double x, double y, double z);

	// ���ö���ŷ����(������)
	// ������Y-X-Z��˳����ת�Ƿ���������Ҫ����

	void SetRotation(const TrekMath::vec3 &eulerAnglesInRadian);
	// ���ö���ŷ����(������)
	// ������Y-X-Z��˳����ת�Ƿ���������Ҫ����

	void SetRotation(double x, double y, double z);

	// ���ö���λ��
	void SetTranslation(const TrekMath::vec3 &position);
	// ���ö���λ��
	void SetTranslation(double x, double y, double z);

	// ָ��ŷ������ת
	void Rotate(const TrekMath::vec3 &eulerAnglesInRadian);

	//// ָ����ԭ��Ϊ����������ת
	//void RotateAxis(const  TrekMath::vec3& axis, double radian);
	//// ָ����pointΪ��ת����������ת
	//void RotateAround(const  TrekMath::vec3& point, const  TrekMath::vec3& axis, double radian);

	// ����ĳһ����ƽ��
	void Translate(const TrekMath::vec3 &direction, double magnitude);

	// �۲�ĳһ��
	void LookAt(const TrekMath::vec3 &target, const TrekMath::vec3 &up = {0.0f, 1.0f, 0.0f});
	// ����ĳһ����۲�
	void LookTo(const TrekMath::vec3 &direction, const TrekMath::vec3 &up = {0.0f, 1.0f, 0.0f});

  private:
  private:
	TrekMath::vec3 m_Scale    = {1.0f, 1.0f, 1.0f};        // ����
	TrekMath::vec3 m_Rotation = {0.f, 0.f, 0.f};           // ��תŷ����(������)
	TrekMath::vec3 m_Position = {0.f, 0.f, 0.f};           // λ��







};
