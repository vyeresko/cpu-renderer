#pragma once

#include "Math/Vector2.h"

namespace renderer {
	class Point2 {
	public:
		Point2() = default;
		Point2(float x, float y);

		Point2 operator+(const Vector2& rhs) const;
		Vector2 operator-(const Point2& rhs) const;

		float x, y;

		static Point2 zero;
	};
}