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

bool Scene::hit(const Ray& r, HitRecord& hr) const
{
	for (auto object : objects)
	{
		object->hit(r, hr);
	}
	return true;
}
