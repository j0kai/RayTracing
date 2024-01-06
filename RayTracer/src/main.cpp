#include <iostream>
#include <stdint.h>

#include "Vec3.h"
#include "Color.h"
#include "Ray.h"

bool TraceRay(const vec3& center, float radius, const Ray& ray)
{
	vec3 origin = ray.Origin - center;
	float a = dot(ray.Direction, ray.Direction);
	float b = 2.0f * dot(origin, ray.Direction);
	float c = dot(origin, origin) - radius*radius;

	float discriminant = b * b - 4.0f * a * c;
	return discriminant > 0.0f;
}

vec3 RayColor(const Ray& ray)
{
	if (TraceRay(vec3(0, 0, -1), 0.5f, ray))
		return vec3(0.8f, 0.2f, 0.3f);
	vec3 unitDirection = unit_vector(ray.Direction);
	auto t = 0.5f * (unitDirection.y() + 1.0f);
	return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
}

int main()
{
	// Image
	const float aspectRatio = 16.0f / 9.0f;
	const uint32_t imageWidth = 400;
	const uint32_t imageHeight = (uint32_t)(imageWidth / aspectRatio);

	// Camera
	float viewportHeight = 2.0f;
	float viewportWidth = aspectRatio * viewportHeight;
	float focalLength = 1.0f;

	vec3 origin = vec3(0, 0, 0);
	vec3 horizontal = vec3(viewportWidth, 0, 0);
	vec3 vertical = vec3(0, viewportHeight, 0);
	auto lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focalLength);

	// Render

	std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

	for (int j = imageHeight - 1; j >= 0; --j)
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < imageWidth; ++i)
		{
			auto h = float(i) / (imageWidth - 1);
			auto v = float(j) / (imageHeight - 1);
			auto direction = lowerLeftCorner + h * horizontal + v * vertical - origin;
			Ray ray(origin, direction);
			vec3 pixelColor = RayColor(ray);
			PrintColor(std::cout, pixelColor);
		}
	}

	std::cerr << "\nDone.\n";
}