#pragma once

#include <iosfwd>

namespace renderer {
	class Vector3 {
	public:
		Vector3() = default;
		Vector3(float x, float y, float z);
		Vector3(float s);

		Vector3(const Vector3& rhs);

		Vector3& operator=(const Vector3& rhs);
		Vector3& operator*=(float c);
		Vector3 operator-(const Vector3& rhs) const;
		Vector3 operator*(float c) const;

		float length() const;
		float dot(const Vector3& rhs) const;
		Vector3 projectOnto(const Vector3& rhs) const;

		friend std::ostream& operator<< (std::ostream& os, Vector3 vector);

		float x, y, z;

		static Vector3 zero;
	};	
}
