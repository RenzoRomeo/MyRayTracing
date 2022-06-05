#pragma once

#include <glm/glm.hpp>

class Material
{
private:
	glm::vec3 color;

public:
	Material(const glm::vec3& color);

	glm::vec3 getColor() const { return color; }
};