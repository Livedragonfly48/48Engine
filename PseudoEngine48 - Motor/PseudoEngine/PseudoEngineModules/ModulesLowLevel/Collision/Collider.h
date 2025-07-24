#pragma once
#include "../Math/Vec2.h"


struct AABB
{
	Vec2 center;
	Vec2 halfSize;

	AABB() : center(0.0f, 0.0f), halfSize(0.0f, 0.0f) {}
	AABB(const Vec2& c, const Vec2& hs) : center(c), halfSize(hs) {}

	Vec2 Min() const { return center - halfSize; }
	Vec2 Max() const { return center + halfSize; }
};


struct CircleCollider
{
	Vec2 center;
	float radius;

	CircleCollider() : center(0.0f, 0.0f), radius(0.0f) {}
	CircleCollider(const Vec2& c, float r) : center(c), radius(r) {}
};
