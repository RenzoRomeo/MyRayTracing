#include <fstream>
#include <iostream>

#include "Renderer.h"
#include "Material.h"

Renderer::Renderer(int width, int height, const Camera& camera, const Scene& scene, int samples, int maxDepth)
	:width(width), height(height), camera(camera), scene(scene), samples(samples), maxDepth(maxDepth)
{
	bufferSize = 3 * width * height;
	buffer = new uint8_t[bufferSize];
}

Renderer::~Renderer()
{
	delete[] buffer;
}

void Renderer::renderScene()
{
	for (int i = 0; i < height; i++)
	{
		std::cout << "\rscanlines left : " << height - i;
		for (int j = 0; j < width; j++)
		{
			glm::vec3 pixelColor = { 0,0,0 };
			for (int samp = 0; samp < samples; samp++)
			{
				float r = ((float)j + glm::linearRand<float>(0, 1)) / (float)(width - 1);
				float s = ((float)i + glm::linearRand<float>(0, 1)) / (float)(height - 1);

				Ray ray = camera.getRay(r, s);

				pixelColor += rayColor(ray, maxDepth);
			}
			pixelColor /= samples;

			int pixelIndex = 3 * (i * width + j);
			buffer[pixelIndex] = (int)pixelColor.x; // r
			buffer[pixelIndex + 1] = (int)pixelColor.y; // g
			buffer[pixelIndex + 2] = (int)pixelColor.z; // b
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

glm::vec3 Renderer::rayColor(const Ray& r, int depth)
{
	HitRecord hr;

	if (depth <= 0)
		return { 0,0,0 };

	if (scene.hit(r, hr, 0.001, INFINITY))
	{
		Ray scattered;
		glm::vec3 attenuation;
		if (hr.material->scatter(r, hr, attenuation, scattered))
		{
			return attenuation * rayColor(scattered, depth - 1);
		}
	}

	float t = 0.5 * (r.d().y + 1.0f);
	return (1.0f - t) * glm::vec3(255, 255, 255) + t * glm::vec3(0.5 * 255, 0.7 * 255, 1.0 * 255);
}
