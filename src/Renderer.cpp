#include <fstream>

#include "Renderer.h"

Renderer::Renderer(int width, int height, const Camera& camera)
	:width(width), height(height), camera(camera)
{
	bufferSize = 3 * width * height;
	buffer = new uint8_t[bufferSize];
}

Renderer::~Renderer()
{
	delete[] buffer;
}

void Renderer::renderScene(const Scene& scene) const
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			glm::vec3 dir = camera.bottomLeft + camera.horizontal * ((float)j / (float)(width - 1))
				+ camera.vertical * ((float)i / (float)(height - 1)) - camera.position;

			Ray r(camera.position, dir);

			HitRecord hr;
			hr.hitColor = { 0,0,0 };
			hr.minT = INFINITY;

			scene.hit(r, hr);

			glm::vec3 color = hr.hitColor;

			int pixelIndex = 3 * (i * width + j);
			buffer[pixelIndex] = (int)color.x; // r
			buffer[pixelIndex + 1] = (int)color.y; // g
			buffer[pixelIndex + 2] = (int)color.z; // b
		}
	}
}

void Renderer::saveImage(const std::string& filepath) const
{
	std::ofstream file(filepath);
	file << "P3\n" << width << " " << height << "\n255\n";
	for (int i = height - 1; i >= 0; i--)
	{
		for (int j = 0; j < width; j++)
		{
			int pixelIndex = 3 * (i * width + j);
			int r = (int)buffer[pixelIndex];
			int g = (int)buffer[pixelIndex + 1];
			int b = (int)buffer[pixelIndex + 2];
			file << r << " " << g << " " << b << '\n';
		}
	}
}
