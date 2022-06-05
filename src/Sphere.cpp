#include "Sphere.h"

Sphere::Sphere(const glm::vec3& center, float radius, const glm::vec3& color, const Material& material)
    : center(center), radius(radius), material(material)
{
}

bool Sphere::hit(const Ray& r, HitRecord& hr) const
{
    glm::vec3 OC = r.o() - center;
    float v1 = glm::dot(r.d(), OC);
    float determinant = v1 * v1 - (glm::dot(OC, OC) - radius * radius);

    if (determinant < 0)
        false;
    
    float t = -v1 - sqrtf(determinant);

    if (t < hr.minT)
    {
        hr.minT = t;

        glm::vec3 hitPoint = r.at(t);
        glm::vec3 hitNormal = glm::normalize(hitPoint - center);

        hr.hitPoint = hitPoint;
        hr.hitNormal = hitNormal;
        hr.hitColor = material.getColor();
    }

    return true;
}
