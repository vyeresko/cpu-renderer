#pragma once

#include "Math/Vector3.h"

namespace renderer {
	class Point3 {
	public:
		Point3() = default;
		Point3(float x, float y, float z);

		Point3 operator+(const Vector3& rhs) const;
		Vector3 operator-(const Point3& rhs) const;

		float x, y, z;

		static Point3 zero;
	};
}