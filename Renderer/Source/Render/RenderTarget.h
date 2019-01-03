#pragma once

#include <iosfwd>

#include "Render/Color.h"

namespace renderer {
	class RenderTarget {
	public:
		RenderTarget(unsigned short width, unsigned short height);

		RGB_8& operator[](int index);

		unsigned short getWidth() const { return m_width; }
		unsigned short getHeight() const { return m_height; }

		void clear(RGB_8 color);

		friend std::ostream& operator<<(std::ostream& os, const RenderTarget& render_target);

	private:
		unsigned short m_width;
		unsigned short m_height;
		RGB_8* m_color_buffer;
	};
}
