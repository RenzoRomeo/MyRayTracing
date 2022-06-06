#include "Scene.h"

Scene::Scene()
{
}

void Scene::add(Hittable* object)
{
	objects.push_back(object);
}

void Scene::clear()
{
	objects.clear();
}

bool Scene::hit(const Ray& r, HitRecord& hr, float tMin, float tMax) const
{
	HitRecord tempRec;
	bool hitAnything = false;

	for (const auto& object : objects)
	{
		if (object->hit(r, tempRec, tMin, tMax))
		{
			hr = tempRec;
			tMax = tempRec.t;
			hitAnything = true;
		}
			
	}
	return hitAnything;
}
