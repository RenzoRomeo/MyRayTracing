#pragma once

#include "Ray.h"

class Material;

struct HitRecord
{
	glm::vec3 hitPoint;
	glm::vec3 hitNormal;
	Material* material = nullptr;
	float t;
	bool frontFace;

	inline void setNormal(const Ray& r, const glm::vec3& normal)
	{
		frontFace = glm::dot(r.d(), normal) < 0;
		hitNormal = frontFace ? normal : -normal;
	}
};

class Hittable
{
public:
	virtual bool hit(const Ray& r, HitRecord& hr, float tMin, float tMax) const = 0;
};