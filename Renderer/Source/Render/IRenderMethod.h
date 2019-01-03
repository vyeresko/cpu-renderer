#pragma once

#include "Render/RenderTarget.h"
#include "Scene/Vertex.h"

namespace renderer {
	class IRenderMethod {
	public:
		virtual void frameStart(const RenderTarget& render_target) = 0; // init all data needed for rendering scene
		virtual void render(const std::array<Vertex, 3>& vertices, RenderTarget& render_target) = 0;
	};
}
