#include "Precompiled.h"

#include "RenderTarget.h"

namespace renderer {
	RenderTarget::RenderTarget(unsigned short width, unsigned short height):
		m_color_buffer(new RGB_8[width * height]), m_width(width), m_height(height)
	{}

	RGB_8& RenderTarget::operator[](int index) { return m_color_buffer[index]; }

	void RenderTarget::clear(RGB_8 color)
	{
		for (int i = 0; i < m_height; ++i)
			for (int j = 0; j < m_width; ++j) 
				m_color_buffer[i * m_width + j] = color;
	}

	std::ostream& operator<<(std::ostream& os, const RenderTarget& render_target)
	{
		os << "P3" << "\n"
			<< render_target.m_width << " "
			<< render_target.m_height << "\n"
			<< 255 << "\n";

		for (unsigned short i = 0; i < render_target.m_height; ++i) {
			for (unsigned short j = 0; j < render_target.m_width; j++) {
				os << +render_target.m_color_buffer[i * render_target.m_width + j].r << '\t';
				os << +render_target.m_color_buffer[i * render_target.m_width + j].g << '\t';
				os << +render_target.m_color_buffer[i * render_target.m_width + j].b << '\t';
			}
			os << '\n';
		}

		return os;
	}
}
