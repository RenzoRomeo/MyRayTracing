#pragma once

#include "Ray.h"

struct HitRecord
{
	glm::vec3 hitPoint;
	glm::vec3 hitNormal;
	glm::vec3 hitColor;
	float minT;
};

class Hittable
{
public:
	virtual bool hit(const Ray& r, HitRecord& hr) const = 0;
};