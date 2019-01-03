#include "Precompiled.h"

#include "Point3.h"

namespace renderer {
	Point3::Point3(float x, float y, float z) :
		x(x), y(y), z(z)
	{}

	Point3 Point3::operator+(const Vector3& rhs) const
	{
		Point3 point(x, y, z);
		point.x += rhs.x;
		point.y += rhs.y;
		point.z += rhs.z;
		
		return point;
	}

	Vector3 Point3::operator-(const Point3& rhs) const
	{
		Vector3 vector(x, y, z);
		vector.x -= rhs.x;
		vector.y -= rhs.y;
		vector.z -= rhs.z;

		return vector;
	}

	Point3 Point3::zero(0.f, 0.f, 0.f);
}
