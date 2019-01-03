#pragma once

#include "Precompiled.h"

#include "Render/Rasterizer/Rasterizer.h"
#include "Math/Point3.h"
#include "Scene/Vertex.h"

namespace renderer {
	class Camera {
	public:
		struct Frustum {
			float near, far;
			float left, right;
			float bottom, top;
		};
		
		Camera(Vector3 offset, Frustum frustum) :
			m_offset(offset), m_frustum(frustum)
		{}

		~Camera() = default;

		Vector3 getOffset() const { return m_offset;  }
		void setOffset(Vector3 offset) { m_offset = m_offset; }

		const Frustum& getFrustum() const { return m_frustum; }
		void setFrustum(const Frustum& frustum) { m_frustum = frustum; }

		void setRenderMethod(std::unique_ptr<IRenderMethod> render_method) { m_render_method = std::move(render_method); }

		void makePhoto(std::vector<Vertex>& vertices, RenderTarget& render_target);

		Point3 projectPoint(const Point3& point);

		static Camera kiev_88;

	private:
		std::unique_ptr<IRenderMethod> m_render_method = nullptr;
		Vector3 m_offset;
		Frustum m_frustum;
	};
};