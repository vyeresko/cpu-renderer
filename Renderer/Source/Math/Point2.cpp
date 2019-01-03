#include "Precompiled.h"

#include "Point2.h"

namespace renderer {
	Point2::Point2(float x, float y) :
		x(x), y(y)
	{}

	Point2 Point2::operator+(const Vector2& rhs) const
	{
		Point2 point(x, y);
		point.x += rhs.x;
		point.y += rhs.y;

		return point;
	}

	Vector2 Point2::operator-(const Point2& rhs) const
	{
		Vector2 vector(x, y);
		vector.x -= rhs.x;
		vector.y -= rhs.y;

		return vector;
	}

	Point2 Point2::zero(0.f, 0.f);
}
