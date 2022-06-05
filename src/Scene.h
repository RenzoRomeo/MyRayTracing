#pragma once

#include <vector>

#include "Hittable.h"

class Scene : public Hittable
{
private:
	std::vector<Hittable*> objects;

public:
	Scene();

	void add(Hittable* object);
	void clear();

	bool hit(const Ray& r, HitRecord& hr) const override;
};