#pragma once

#include "Render/Color.h"
#include "Render/IRenderMethod.h"
#include "Scene/Vertex.h"

namespace renderer {
	class Point2;

	class Rasterizer: public IRenderMethod {
	public:
		Rasterizer() = default;
		~Rasterizer();

		void frameStart(const RenderTarget& render_target) override;
		void render(const std::array<Vertex, 3>& vertices, RenderTarget& render_target) override;
		
	private:
		void allocateDepthBuffer(const RenderTarget& render_target);
		void transformToScreen();
		float edgeTest(const Point2& v0, const Point2& v1, const Point2& p);

		struct DepthBuffer {
			unsigned short width = 0;
			unsigned short height = 0;
			unsigned short* data = nullptr;
		} m_depth_buffer;
	};
}