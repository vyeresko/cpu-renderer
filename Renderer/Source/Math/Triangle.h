#pragma once

namespace renderer {
	template<typename T>
	class Triangle {
	public:
		Triangle():
			m_vertices{ T::zero, T::zero, T::zero }
		{}

		Triangle(T v1, T v2, T v3):
			m_vertices{ v1, v2, v3 }
		{}

		~Triangle() = default;
		
		T& operator[](int index)
		{
			return m_vertices[index];
		}

		float area() const
		{
			auto a = m_vertices[0] - m_vertices[1];
			auto b = m_vertices[2] - m_vertices[1];

			return 0.5f * (a - a.projectOnto(b)).length() * b.length();
		}

	private:
		std::array<T, 3> m_vertices;
	};
}