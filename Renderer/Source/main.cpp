#include "Precompiled.h"

#include <fstream>

#include "Render/Camera.h"
#include "Render/Color.h"
#include "Math/Triangle.h"
#include "Render/Rasterizer/Rasterizer.h"
#include "Render/RenderTarget.h"
#include "Scene/Vertex.h"

using renderer::Camera;
using renderer::Point3;
using renderer::Rasterizer;
using renderer::RenderTarget;
using renderer::RGB_8;
using renderer::Vector3;
using renderer::Vertex;

int main()
{
	std::vector<Vertex> vertices = {
		{ Point3(-5.f, -2.f, 2.f), { 0.f, 0.f, 1.f } },
		{ Point3(5.f, -3.f, 2.f), { 0.f, 1.f, 0.f } },
		{ Point3(2.f, 4.5f, 4.f), { 1.f, 0.f, 0.f } },
		{ Point3(-5.f, -2.f, 2.2f), { 1.f, 0.6f, 1.f } },
		{ Point3(7.f, -3.f, 2.2f), { 0.f, 0.6f, 0.5f } },
		{ Point3(-1.f, 2.f, 2.2f), { 1.f, 0.3f, 0.2f } }
	};
	
	RenderTarget render_target(1280, 860);
	render_target.clear(RGB_8{ 0, 0, 0 });

	Camera::kiev_88.setRenderMethod(std::make_unique<Rasterizer>());
	Camera::kiev_88.makePhoto(vertices, render_target);

	std::cout << "Writing to the image...\n";
	std::fstream image_file("test.ppm");
	image_file << render_target;
	std::cout << "Done.";
}