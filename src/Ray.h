#pragma once

#include <glm/glm.hpp>

class Ray
{
private:
	glm::vec3 origin;
	glm::vec3 direction;

public:
	Ray(const glm::vec3& origin, const glm::vec3& direction);

	glm::vec3 at(float t) const;

	glm::vec3 o() const { return origin; }

	glm::vec3 d() const { return direction; }
};