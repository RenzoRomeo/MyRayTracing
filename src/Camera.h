#pragma once

#include <glm/glm.hpp>

#include "Ray.h"

struct Camera
{
private:
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 up;

	glm::vec3 w, u, v;
	glm::vec3 horizontal, vertical;
	glm::vec3 bottomLeft;

	float fov;
	float focalDistance;
	float viewportW, viewportH;

public:
	Camera(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& up, float focalDistance, float fov);

	Ray getRay(float r, float s) const;
};