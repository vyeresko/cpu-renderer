#include "Precompiled.h"

#include "Camera.h"

#include <assert.h>

#include "Math/Triangle.h"

namespace renderer {
	void Camera::makePhoto(std::vector<Vertex>& vertices, RenderTarget& render_target)
	{
		// TODO: round vertices
		// to the nearest multiple
		// of 3

		assert(m_render_method != nullptr);

		unsigned short vertex_counter = 0;
		
		std::array<Vertex, 3> render_pack;

		m_render_method->frameStart(render_target);

		for (auto vertex : vertices) {
			render_pack[vertex_counter].position = projectPoint(vertex.position);
			render_pack[vertex_counter].color = vertex.color;

			++vertex_counter;

			if (vertex_counter == 3) {
				// Reset counter
				vertex_counter = 0;

				// Draw triangle
				m_render_method->render(render_pack, render_target);
			}
		}
	}

	Point3 Camera::projectPoint(const Point3& vertex)
	{
		// Transform to camera space (world space -> camera space)
		Point3 projected_point{ vertex.x + m_offset.x, vertex.y + m_offset.y, vertex.z + m_offset.z };

		// Project vertex (camera space -> screen space(projection space?))
		projected_point.x = (m_frustum.near * projected_point.x) / projected_point.z;
		projected_point.y = (m_frustum.near * projected_point.y) / projected_point.z;
		projected_point.z = projected_point.z;

		// Clip vertex (screen space(projection space?) -> NDC)
		projected_point.x = 2 * projected_point.x / (m_frustum.right - m_frustum.left);
		projected_point.y = 2 * projected_point.y / (m_frustum.top - m_frustum.bottom);

		return projected_point;
	}

	Camera Camera::kiev_88(Vector3(0.f, 0.f, -1.f),
		{ 1.f, 10.f,	// near far
		-10.f, 10.f,	// left right
		-5.f, 5.f } // bottom top
	);
}
