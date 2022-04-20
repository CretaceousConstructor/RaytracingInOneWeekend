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

	// 获取对象缩放比例
	TrekMath::vec3 GetScale() const;

	// 获取对象欧拉角(弧度制)
	// 对象以Y-X-Z轴顺序旋转?是否是这样需要测试
	TrekMath::vec3 GetRotation() const;

	// 获取对象位置
	TrekMath::vec3 GetPosition() const;

	// 获取右方向轴
	TrekMath::vec3 GetRightAxis() const;

	// 获取上方向轴
	TrekMath::vec3 GetUpAxis() const;

	// 获取前方向轴
	TrekMath::vec3 GetForwardAxis() const;

	// 获取世界变换矩阵
	TrekMath::mat4 GetLocalToWorldMatrix() const;

	// 获取逆世界变换矩阵
	TrekMath::mat4 GetWorldToLocalMatrix() const;

	// 设置对象缩放比例
	void SetScale(const TrekMath::vec3 &scale);
	// 设置对象缩放比例
	void SetScale(double x, double y, double z);

	// 设置对象欧拉角(弧度制)
	// 对象将以Y-X-Z轴顺序旋转是否是这样需要测试

	void SetRotation(const TrekMath::vec3 &eulerAnglesInRadian);
	// 设置对象欧拉角(弧度制)
	// 对象以Y-X-Z轴顺序旋转是否是这样需要测试

	void SetRotation(double x, double y, double z);

	// 设置对象位移
	void SetTranslation(const TrekMath::vec3 &position);
	// 设置对象位移
	void SetTranslation(double x, double y, double z);

	// 指定欧拉角旋转
	void Rotate(const TrekMath::vec3 &eulerAnglesInRadian);

	//// 指定以原点为中心绕轴旋转
	//void RotateAxis(const  TrekMath::vec3& axis, double radian);
	//// 指定以point为旋转中心绕轴旋转
	//void RotateAround(const  TrekMath::vec3& point, const  TrekMath::vec3& axis, double radian);

	// 沿着某一方向平移
	void Translate(const TrekMath::vec3 &direction, double magnitude);

	// 观察某一点
	void LookAt(const TrekMath::vec3 &target, const TrekMath::vec3 &up = {0.0f, 1.0f, 0.0f});
	// 沿着某一方向观察
	void LookTo(const TrekMath::vec3 &direction, const TrekMath::vec3 &up = {0.0f, 1.0f, 0.0f});

  private:
  private:
	TrekMath::vec3 m_Scale    = {1.0f, 1.0f, 1.0f};        // 缩放
	TrekMath::vec3 m_Rotation = {0.f, 0.f, 0.f};           // 旋转欧拉角(弧度制)
	TrekMath::vec3 m_Position = {0.f, 0.f, 0.f};           // 位置







};
