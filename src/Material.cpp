#include <glm/gtc/random.hpp>

#include "Material.h"

Opaque::Opaque(const glm::vec3& color)
	:color(color)
{
}

bool Opaque::scatter(const Ray& rIn, const HitRecord& rec, glm::vec3& attenuation, Ray& scattered) const
{
	glm::vec3 scatterDir = rec.hitNormal + glm::sphericalRand(1.0f);
	scattered = Ray(rec.hitPoint, scatterDir);
	attenuation = color;
	return true;
}
