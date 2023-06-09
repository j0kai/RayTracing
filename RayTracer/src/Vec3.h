#pragma once

#include <cmath>
#include <iostream>
#include <array>

using std::sqrt;

class Vec3
{
public:
	Vec3() : e{ 0, 0, 0 } {}
	Vec3(float ue) : e{ ue, ue, ue } {} // ue = uniform element - used when you want to init each element as the same value
	Vec3(float e1, float e2, float e3) : e{ e1, e2, e3 } {}

	float x() const { return e[0]; }
	float y() const { return e[1]; }
	float z() const { return e[2]; }

	float r() const { return e[0]; }
	float g() const { return e[1]; }
	float b() const { return e[2]; }

	Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
	float operator[](int i) const { return e[i]; }
	float& operator[](int i) { return e[i]; }

	Vec3& operator+=(const Vec3& other)
	{
		e[0] += other[0];
		e[1] += other[1];
		e[2] += other[2];
		return *this;
	}

	Vec3& operator*=(const float t)
	{
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	}

	Vec3& operator/=(const float t)
	{
		return *this *= 1 / t;
	}

	inline float length() const { return sqrt(length_squared()); }
	inline float length_squared() const
	{
		return e[0] * e[0]
			+ e[1] * e[1]
			+ e[2] * e[2];
	}

public:
	std::array<float, 3> e;
};

// Utility Functions
inline std::ostream& operator<<(std::ostream& os, const Vec3& v)
{
	return os << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline Vec3 operator+(const Vec3& u, const Vec3& v)
{
	return Vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline Vec3 operator-(const Vec3& u, const Vec3& v)
{
	return Vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline Vec3 operator*(const Vec3& u, const Vec3& v)
{
	return Vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline Vec3 operator*(float t, const Vec3& v)
{
	return Vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline Vec3 operator*(const Vec3& v, float t)
{
	return t * v;
}

inline Vec3 operator/(Vec3& v, float t)
{
	return (1 / t) * v;
}

inline float dot(const Vec3& u, const Vec3& v)
{
	return u.e[0] * v.e[0]
		+ u.e[1] * v.e[1]
		+ u.e[2] * v.e[2];
}

inline Vec3 cross(const Vec3& u, const Vec3& v)
{
	return Vec3(u.e[1] * v.e[2] - u.e[2] * u.e[1],
		u.e[2] * v.e[0] - u.e[0] * u.e[2],
		u.e[0] * v.e[1] - u.e[1] * u.e[0]);
}

inline Vec3 unit_vector(Vec3 v) { return v / v.length(); }