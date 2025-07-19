#pragma once
#include "../Math/Vec2.h"

struct Ray
{
	Vec2 origin;
	Vec2 direction;
};

struct LineSegment
{
	Vec2 start;
	Vec2 end;
};

struct RaycastResult
{
	bool hit = false;
	Vec2 point = Vec2(0.0f, 0.0f);
	float distance = 0.0f;
};

RaycastResult Raycast(const Ray& ray, const LineSegment& segment);
