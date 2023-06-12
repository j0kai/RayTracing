#include <iostream>

#include "Vec3.h"
#include "Color.h"
#include "Ray.h"

Vec3 RayColor(const Ray& ray)
{
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
	auto viewportHeight = 2.0f;
	auto viewportWidth = aspectRatio * viewportHeight;
	auto focalLength = 1.0f;

	auto origin = Vec3(0, 0, 0);
	auto horizontal = Vec3(viewportWidth, 0, 0);
	auto vertical = Vec3(0, viewportHeight, 0);
	auto lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, focalLength);

	// Render

	std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

	for (int j = imageHeight - 1; j >= 0; --j)
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < imageWidth; ++i)
		{
			auto u = float(i) / (imageWidth - 1);
			auto v = float(j) / (imageHeight - 1);
			auto direction = lowerLeftCorner + u * horizontal + v * vertical - origin;
			Ray ray(origin, direction);
			Vec3 pixelColor = RayColor(ray);
			PrintColor(std::cout, pixelColor);
		}
	}

	std::cerr << "\nFinished.\n";
}