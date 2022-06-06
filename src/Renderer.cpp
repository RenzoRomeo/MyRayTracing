#include <fstream>
#include <iostream>
#include <chrono>

#include "Renderer.h"
#include "Material.h"

Renderer::Renderer(int width, int height, const Camera& camera, const Scene& scene, int samples, int maxDepth, int threads)
	:width(width), height(height), camera(camera), scene(scene), samples(samples), maxDepth(maxDepth), nThreads(threads)
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
	using std::chrono::high_resolution_clock;
	using std::chrono::duration_cast;
	using std::chrono::duration;

	int linesPerThread = ceil(height / nThreads);

	auto t1 = high_resolution_clock::now();

	for (int i = 0; i < nThreads; i++)
	{
		int beginning = i * linesPerThread;
		int end = (i + 1)  * linesPerThread;

		if (end > height)
			end = height;

		threadPool.push_back(std::thread([=] { renderSection(beginning, end); }));
	}

	for (auto& thread : threadPool)
		if (thread.joinable())
			thread.join();

	auto t2 = high_resolution_clock::now();
	duration<double, std::milli> msDouble = t2 - t1;

	std::cout << "\nDone [" << msDouble.count() / 1000.0 << " s]\n";
}

void Renderer::renderLine(int line)
{
	for (int j = 0; j < width; j++)
	{
		glm::vec3 pixelColor = { 0,0,0 };
		for (int samp = 0; samp < samples; samp++)
		{
			float r = ((float)j + glm::linearRand<float>(0, 1)) / (float)(width - 1);
			float s = ((float)line + glm::linearRand<float>(0, 1)) / (float)(height - 1);

			Ray ray = camera.getRay(r, s);

			pixelColor += rayColor(ray, maxDepth);
		}
		pixelColor /= samples;
		pixelColor = glm::sqrt(pixelColor);

		int pixelIndex = 3 * (line * width + j);
		buffer[pixelIndex] = (uint8_t)(254.999 * pixelColor.x); // r
		buffer[pixelIndex + 1] = (uint8_t)(254.999 * pixelColor.y); // g
		buffer[pixelIndex + 2] = (uint8_t)(254.999 * pixelColor.z); // b
	}
}

void Renderer::renderSection(int beginning, int end)
{
	for (int i = beginning; i < end; i++)
	{
		renderLine(i);
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
	return (1.0f - t) * glm::vec3(1, 1, 1) + t * glm::vec3(0.5, 0.7, 1.0);
}
