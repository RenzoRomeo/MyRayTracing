#pragma once

#include "Ray.h"

class Material;

struct HitRecord
{
	glm::vec3 hitPoint;
	glm::vec3 hitNormal;
	Material* material = nullptr;
	float t;
};

class Hittable
{
public:
	virtual bool hit(const Ray& r, HitRecord& hr, float tMin, float tMax) const = 0;
};