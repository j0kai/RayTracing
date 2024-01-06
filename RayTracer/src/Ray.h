#pragma once

#include "Vec3.h"

struct Ray
{
	vec3 Origin;
	vec3 Direction;

	Ray(): Origin(0.0f), Direction(0.0f) {}
	Ray(const Vec3& o, const Vec3& d) : Origin(o), Direction(d) {}
};

// Might delete this if I don't find it useful
// but as of now I'll code it to follow the book
inline vec3 at(const Ray& ray, float t)
{
	return ray.Origin + t * ray.Direction;
}