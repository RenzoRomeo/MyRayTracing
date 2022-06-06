#include "Camera.h"

Camera::Camera(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& up, float focalDistance, float fov)
	:position(position), focalDistance(focalDistance), fov(fov)
{
	this->direction = glm::normalize(direction);
	this->up = glm::normalize(up);

	w = direction; // y
	u = up; // z
	v = glm::cross(w, u); // x

	float aspectRatio = 16.0 / 9.0;
	float tetha = fov * 3.14159265358f / 180.0f;
	float h = tanf(tetha / 2.0f);

	viewportH = h * 2.0;
	viewportW = aspectRatio * viewportH;

	horizontal = v * (float)viewportW;
	vertical = u * (float)viewportH;
	bottomLeft = position + w * focalDistance - vertical / 2.0f - horizontal / 2.0f;
}

Ray Camera::getRay(float r, float s) const
{
	// glm::vec2 rd = glm::diskRand(1.0f);
	// glm::vec3 rd3 = { rd.x, rd.y, 0 };
	// glm::vec3 offset = v * rd.x + u * rd.y;
	glm::vec3 dir = bottomLeft + horizontal * r + vertical * s - position;
	return Ray(position, dir);
}
