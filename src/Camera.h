#pragma once

#include <glm/glm.hpp>

struct Camera
{
public:
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
};