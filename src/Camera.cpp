#include "Camera.h"

Camera::Camera(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& up, float focalDistance, float fov)
	:position(position), focalDistance(focalDistance), fov(fov)
{
	this->direction = glm::normalize(direction);
	this->up = glm::normalize(up);

	w = direction;
	u = up;
	v = glm::cross(w, u);

	float aspectRatio = 16.0 / 9.0;
	float tetha = fov * 3.14159265358f / 180.0f;
	float h = tanf(tetha / 2.0f);

	viewportH = h * 2.0;
	viewportW = aspectRatio * viewportH;

	horizontal = v * (float)viewportW;
	vertical = u * (float)viewportH;
	bottomLeft = position + w * focalDistance - vertical / 2.0f - horizontal / 2.0f;
}
