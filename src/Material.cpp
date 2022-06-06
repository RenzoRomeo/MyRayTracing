#include <glm/gtc/random.hpp>

#include "Material.h"

Opaque::Opaque(const glm::vec3& color)
	: color(color)
{
}

bool Opaque::scatter(const Ray& r, const HitRecord& rec, glm::vec3& attenuation, Ray& scattered) const
{
	glm::vec3 scatterDir = rec.hitNormal + glm::sphericalRand(1.0f);
	scattered = Ray(rec.hitPoint, scatterDir);
	attenuation = color;
	return true;
}

Metal::Metal(const glm::vec3& color, float fuzz)
	: color(color), fuzz(fuzz)
{
}

bool Metal::scatter(const Ray& r, const HitRecord& rec, glm::vec3& attenuation, Ray& scattered) const
{
	glm::vec3 v = r.d();
	glm::vec3 n = rec.hitNormal;
	glm::vec3 reflected = v - 2.0f * (glm::dot(v, n) * n);
	scattered = Ray(rec.hitPoint, reflected + fuzz * glm::ballRand(1.0f));
	attenuation = color;
	return glm::dot(scattered.d(), rec.hitNormal) > 0;
}
