

#include "transform.h"

transform::transform(const TrekMath::vec3 &scale, const TrekMath::vec3 &rotation, const TrekMath::vec3 &position)

    :
    m_Scale(scale),
    m_Rotation(rotation),
    m_Position(position)
{
}

TrekMath::vec3 transform::GetScale() const
{
	return m_Scale;
}

TrekMath::vec3 transform::GetRotation() const
{
	return m_Rotation;
}

TrekMath::vec3 transform::GetPosition() const
{
	return m_Position;
}

TrekMath::vec3 transform::GetRightAxis() const
{
	//y = yaw
	//x == pitch
	//z = roll
	auto R = glm::yawPitchRoll(m_Rotation.y, m_Rotation.x, m_Rotation.z);

	//GLM 都是列主矩阵
	TrekMath::vec3 result = R[0];
	return result;
}

TrekMath::vec3 transform::GetUpAxis() const
{
	//x == pitch
	//y = yaw
	//z = roll
	auto R = glm::yawPitchRoll(m_Rotation.y, m_Rotation.x, m_Rotation.z);
	//GLM 都是列主矩阵

	TrekMath::vec3 result = R[1];

	return result;
}

TrekMath::vec3 transform::GetForwardAxis() const
{
	//x == pitch
	//y = yaw
	//z = roll
	auto R = glm::yawPitchRoll(m_Rotation.y, m_Rotation.x, m_Rotation.z);
	//GLM 都是列主矩阵

	TrekMath::vec3 result = R[2];

	return result;
}

TrekMath::mat4 transform::GetLocalToWorldMatrix() const
{
	const auto world = glm::translate(TrekMath::mat4(1.0f), m_Position) * glm::yawPitchRoll(m_Rotation.y, m_Rotation.x, m_Rotation.z) *
	                   glm::scale(TrekMath::mat4(1.0f), m_Scale);
	return world;
}

TrekMath::mat4 transform::GetWorldToLocalMatrix() const
{
	auto InvWorld = glm::inverse(GetLocalToWorldMatrix());

	return InvWorld;
}

void transform::SetScale(const TrekMath::vec3 &scale)
{
	m_Scale = scale;
}

void transform::SetScale(double x, double y, double z)
{
	m_Scale.x = x;
	m_Scale.y = y;
	m_Scale.z = z;
}

void transform::SetRotation(const TrekMath::vec3 &eulerAnglesInRadian)
{
	m_Rotation = eulerAnglesInRadian;
}

void transform::SetRotation(double x, double y, double z)
{
	m_Rotation.x = x;
	m_Rotation.y = y;
	m_Rotation.z = z;
}

void transform::SetTranslation(const TrekMath::vec3 &position)
{
	m_Position = position;
}

void transform::SetTranslation(double x, double y, double z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

void transform::Rotate(const TrekMath::vec3 &eulerAnglesInRadian)
{
	m_Rotation = m_Rotation + eulerAnglesInRadian;
}

void transform::Translate(const TrekMath::vec3 &direction, double magnitude)
{
	m_Position = m_Position + magnitude * direction;
}

void transform::LookAt(const TrekMath::vec3 &target, const TrekMath::vec3 &up)
{
	auto view    = glm::lookAtRH(m_Position, target, up);
	auto InvView = glm::inverse(view);
	glm::extractEulerAngleYXZ(InvView, m_Rotation.y, m_Rotation.x, m_Rotation.z);
}

void transform::LookTo(const TrekMath::vec3 &direction, const TrekMath::vec3 &up)
{
	auto target = m_Position + direction;
	this->LookAt(target, up);
}
