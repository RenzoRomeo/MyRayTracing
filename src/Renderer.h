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

public:
	Renderer(int width, int height, const Camera& camera);
	~Renderer();

	void renderScene(const Scene& scene) const;
	void saveImage(const std::string& filepath) const;
};