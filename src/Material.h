#pragma once

#include <glm/glm.hpp>

#include "Hittable.h"

class Material
{
public:
	virtual bool scatter(const Ray& rIn, const HitRecord& rec, glm::vec3& attenuation, Ray& scattered) const = 0;
};

class Opaque : public Material
{
public:
	glm::vec3 color;

public:
	Opaque(const glm::vec3& color);

	virtual bool scatter(const Ray& rIn, const HitRecord& rec, glm::vec3& attenuation, Ray& scattered) const override;
};