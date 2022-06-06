#include "Sphere.h"

Sphere::Sphere(const glm::vec3& center, float radius, const glm::vec3& color, Material* material)
    : center(center), radius(radius), material(material)
{
}

bool Sphere::hit(const Ray& r, HitRecord& hr, float tMin, float tMax) const
{
    glm::vec3 OC = r.o() - center;
    float v1 = glm::dot(r.d(), OC);
    float discriminant = v1 * v1 - (glm::dot(OC, OC) - radius * radius);

    if (discriminant < 0)
        return false;
    
    float t = -v1 - sqrtf(discriminant);

    if (t < tMin || t > tMax)
        return false;

    glm::vec3 hitPoint = r.at(t);
    glm::vec3 hitNormal = glm::normalize(hitPoint - center);

    hr.t = t;
    hr.hitPoint = hitPoint;
    hr.hitNormal = hitNormal;
    hr.material = material;

    return true;
}
