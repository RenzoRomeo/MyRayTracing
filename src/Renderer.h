#pragma once

#include <cstdint>
#include <string>

#include <glm/glm.hpp>

#include "Camera.h"
#include "Scene.h"

class Renderer
{
private:
	int width;
	int height;
	int bufferSize;
	uint8_t *buffer;
	Camera camera;
	Scene scene;

public:
	Renderer(int width, int height, const Camera& camera, const Scene& scene);
	~Renderer();

	glm::vec3 rayColor(const Ray& r, int depth);

	void renderScene();
	void saveImage(const std::string& filepath) const;
};