#pragma once

namespace renderer {
	class Vector2 {
	public:
		Vector2() = default;
		Vector2(float x, float y);
		Vector2(float s);

		Vector2(const Vector2& rhs);

		Vector2& operator=(const Vector2& rhs);
		Vector2 operator-(const Vector2& rhs) const;
		Vector2 operator*(float c) const;

		float length() const;
		float dot(const Vector2& rhs) const;
		Vector2 projectOnto(const Vector2& rhs) const;

		friend std::ostream& operator<< (std::ostream& os, Vector2 vector);

		float x, y;

		static Vector2 zero;
	};
}
