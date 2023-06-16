#include <iostream>

#include "Vec3.h"
#include "Color.h"
#include "Ray.h"

bool TraceRay(const Vec3& center, float radius, const Ray& ray)
{
	Vec3 origin = ray.Origin - center;
	float a = dot(ray.Direction, ray.Direction);
	float b = 2.0f * dot(origin, ray.Direction);
	float c = dot(origin, origin) - radius*radius;

	float discriminant = b * b - 4.0f * a * c;
	return discriminant > 0.0f;
}

Vec3 RayColor(const Ray& ray)
{
	if (TraceRay(Vec3(0, 0, -1), 0.5f, ray))
		return Vec3(0.8f, 0.2f, 0.3f);
	Vec3 unitDirection = unit_vector(ray.Direction);
	auto t = 0.5f * (unitDirection.y() + 1.0f);
	return (1.0f - t) * Vec3(1.0f, 1.0f, 1.0f) + t * Vec3(0.5f, 0.7f, 1.0f);
}

int main()
{
	// Image
	const float aspectRatio = 16.0f / 9.0f;
	const int imageWidth = 400;
	const int imageHeight = static_cast<int>(imageWidth / aspectRatio);

	// Camera
	float viewportHeight = 2.0f;
	float viewportWidth = aspectRatio * viewportHeight;
	float focalLength = 1.0f;

	Vec3 origin = Vec3(0, 0, 0);
	Vec3 horizontal = Vec3(viewportWidth, 0, 0);
	Vec3 vertical = Vec3(0, viewportHeight, 0);
	auto lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, focalLength);

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
			Vec3 pixelColor = RayColor(ray);
			PrintColor(std::cout, pixelColor);
		}
	}

	std::cerr << "\nDone.\n";
}