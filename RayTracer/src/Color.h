#pragma once

#include "Vec3.h"
#include <iostream>

void PrintColor(std::ostream& os, Vec3 pixelColor)
{
	// Write the translated [0, 255] value of each color channel.
	os << static_cast<int>(255.0f * pixelColor.r()) << ' '
		<< static_cast<int>(255.0f * pixelColor.g()) << ' '
		<< static_cast<int>(255.0f * pixelColor.b()) << '\n';
}