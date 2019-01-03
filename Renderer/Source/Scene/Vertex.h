#pragma once

#include "Render/Color.h"
#include "Math/Point3.h"

namespace renderer  {
	struct Vertex {
		// attributes
		Point3 position;
		Vector3 color;
	};
}