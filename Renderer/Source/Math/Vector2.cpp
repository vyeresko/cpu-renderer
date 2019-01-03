#include "Precompiled.h"

#include "Vector2.h"

namespace renderer {
	Vector2::Vector2(float x, float y) :
		x(x), y(y)
	{}

	Vector2::Vector2(float s) :
		x(s), y(s)
	{}

	Vector2::Vector2(const Vector2& rhs) :
		x(rhs.x), y(rhs.y)
	{}

	Vector2& Vector2::operator=(const Vector2& rhs)
	{
		x = rhs.x;
		y = rhs.y;

		return *this;
	}

	Vector2 Vector2::operator-(const Vector2& rhs) const
	{
		return { x - rhs.x, y - rhs.y };
	}

	Vector2 Vector2::operator*(float c) const
	{
		return { x * c, y * c };
	}

	float Vector2::length() const
	{
		return std::sqrt(x * x + y * y);
	}
	
	float Vector2::dot(const Vector2& rhs) const
	{
		return x * rhs.x + y * rhs.y;
	}
	
	Vector2 Vector2::projectOnto(const Vector2& rhs) const
	{
		return rhs * (this->dot(rhs) / rhs.dot(rhs));
	}

	std::ostream& operator<< (std::ostream& os, Vector2 vector)
	{
		os << "X: " << vector.x << '\n' << "Y: " << vector.y;
		return os;
	}

	Vector2 Vector2::zero(0.f, 0.f);
}
