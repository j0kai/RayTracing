#include <iostream>

#include "Vec3.h"
#include "Color.h"

int main()
{
	const int imageWidth = 256;
	const int imageHeight = 256;

	std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

	for (int j = imageHeight - 1; j >= 0; --j)
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < imageWidth; ++i)
		{
			vec3 pixelColor = { float(i) / (imageWidth - 1), float(j) / (imageHeight - 1), 0.25f };
			PrintColor(std::cout, pixelColor);
		}
	}

	std::cerr << "\nFinished.\n";
}