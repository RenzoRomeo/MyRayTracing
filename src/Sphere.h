#pragma once

#include "Hittable.h"
#include "Material.h"

class Sphere : public Hittable
{
private:
	glm::vec3 center;
	float radius;
	Material* material;

public:
	Sphere(const glm::vec3& center, float radius, const glm::vec3& color, Material *material);

	bool hit(const Ray& r, HitRecord& hr, float tMin, float tMax) const override;
};