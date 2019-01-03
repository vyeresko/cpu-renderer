#include "Precompiled.h"

#include "Rasterizer.h"

#include "Math/Point2.h"
#include "Math/Triangle.h"

namespace renderer {
	Rasterizer::~Rasterizer()
	{
		delete m_depth_buffer.data;
	}

	void Rasterizer::frameStart(const RenderTarget& render_target)
	{
		allocateDepthBuffer(render_target);

		// Clear depth buffer before render
		if (m_depth_buffer.data != nullptr)
			for (int i = 0; i < m_depth_buffer.width * m_depth_buffer.height; ++i)
				m_depth_buffer.data[i] = std::numeric_limits<unsigned short>::max();
	}

	void Rasterizer::render(const std::array<Vertex, 3>& vertices, RenderTarget& render_target)
	{
		Triangle<Point2> screen_triangle;
		auto width = render_target.getWidth();
		auto height = render_target.getHeight();

		// Bounding box for triangle overlap
		float x_max = 0.f, y_max = 0.f;
		float x_min = width, y_min = height;

		for (size_t i = 0; i < vertices.size(); ++i) {

			// Transfom NDC to screen/window coordinates
			screen_triangle[i].x = (vertices[i].position.x + 1.f) * width / 2;
			screen_triangle[i].y = ((vertices[i].position.y + 1.f) * (height / 2) - height) * -1.f; // invert y coordinate

			// Update bounding box
			float x_clamped = std::min<float>(width, std::max(0.f, screen_triangle[i].x));
			float y_clamped = std::min<float>(height, std::max(0.f, screen_triangle[i].y));

			if (x_min > x_clamped)
				x_min = x_clamped;

			if (x_max < x_clamped)
				x_max = x_clamped;

			if (y_min > y_clamped)
				y_min = y_clamped;

			if (y_max < y_clamped)
				y_max = y_clamped;
		}

		auto area = screen_triangle.area();
		
		// Precomputed data for perspective correct attribute interpolation
		auto inverse_c0 = vertices[0].color * (1.f / vertices[0].position.z);
		auto inverse_c1 = vertices[1].color * (1.f / vertices[1].position.z);
		auto inverse_c2 = vertices[2].color * (1.f / vertices[2].position.z);

		auto inverse_z0 = 1.f / vertices[0].position.z;
		auto inverse_z1 = 1.f / vertices[1].position.z;
		auto inverse_z2 = 1.f / vertices[2].position.z;
		//
		
		// Fill the overlapped pixels
		for (unsigned short i = y_min; i < y_max; ++i) {
			for (unsigned short j = x_min; j < x_max; ++j) {
				Point2 p(j, i);

				float e01 = edgeTest(screen_triangle[0], screen_triangle[1], p);
				float e12 = edgeTest(screen_triangle[1], screen_triangle[2], p);
				float e20 = edgeTest(screen_triangle[2], screen_triangle[0], p);

				if (e01 >= 0 && e12 >= 0 && e20 >= 0) {
					// Convert to barycentric coordinates
					float w0 = 0.5f * e12 / area;
					float w1 = 0.5f * e20 / area;
					float w2 = 0.5f * e01 / area;

					// Calculate z				
					float z = 1 / (w0 * inverse_z0 + w1 * inverse_z1 + w2 * inverse_z2);

					// Depth test
					if (m_depth_buffer.data[i * width + j] < z)
						continue;

					m_depth_buffer.data[i * width + j] = z;

					// Calculate colors
					float red = w0 * inverse_c0.x + w1 * inverse_c1.x + w2 * inverse_c2.x;
					float green = w0 * inverse_c0.y + w1 * inverse_c1.y + w2 * inverse_c2.y;
					float blue = w0 * inverse_c0.z + w1 * inverse_c1.z + w2 * inverse_c2.z;
					// Perspective correct attribute interpolation
					red *= z;
					green *= z;
					blue *= z;

					render_target[i * width + j].r = (uint8_t)(red * 255.f);
					render_target[i * width + j].g = (uint8_t)(green * 255.f);
					render_target[i * width + j].b = (uint8_t)(blue * 255.f);
				}
			}
		}
	}

	void Rasterizer::allocateDepthBuffer(const RenderTarget& render_target)
	{
			m_depth_buffer.data = new unsigned short[render_target.getWidth() * render_target.getHeight()];
			m_depth_buffer.width = render_target.getWidth();
			m_depth_buffer.height = render_target.getHeight();
	}

	float Rasterizer::edgeTest(const Point2& v0, const Point2& v1, const Point2& p)
	{
		auto vertices_vector = v1 - v0;
		auto point_vector = p - v0;
		return point_vector.x * vertices_vector.y - point_vector.y * vertices_vector.x;
	}
}