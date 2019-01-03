#include "Precompiled.h"

#include "Vector3.h"

namespace renderer {
	Vector3::Vector3(float x, float y, float z):
		x(x), y(y), z(z)
	{}
	
	Vector3::Vector3(float s):
		x(s), y(s), z(s)
	{}
	
	Vector3::Vector3(const Vector3& rhs):
		x(rhs.x), y(rhs.y), z(rhs.z)
	{}

	Vector3& Vector3::operator=(const Vector3& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;

		return *this;
	}

	Vector3& Vector3::operator*=(float c)
	{
		x *= c;
		y *= c;
		z *= c;

		return *this;
	}

	Vector3 Vector3::operator-(const Vector3& rhs) const
	{
		return { x - rhs.x, y - rhs.y, z - rhs.z };
	}

	Vector3 Vector3::operator*(float c) const
	{
		return { x * c, y * c, z * c };
	}

	float Vector3::length() const
	{
		return std::sqrt(x * x + y * y + z * z);
	}
	
	float Vector3::dot(const Vector3& rhs) const
	{
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}
	
	Vector3 Vector3::projectOnto(const Vector3& rhs) const
	{
		return rhs * (this->dot(rhs) / rhs.dot(rhs));
	}

	std::ostream& operator<< (std::ostream& os, Vector3 vector)
	{
		os << "X: " << vector.x << '\n' << "Y: " << vector.y << '\n' << "Z: " << vector.z;
		return os;
	}

	 Vector3 Vector3::zero(0.f, 0.f, 0.f);
}
