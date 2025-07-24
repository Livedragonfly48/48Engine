#pragma once
#include "Collider.h"


struct CollisionResult
{
	bool collided = false;
	Vec2 normal = Vec2(0.0f, 0.0f);
	float penetration = 0.0f;
};


CollisionResult AABBvsAABB(const AABB& a, const AABB& b);
CollisionResult CirclevsCircle(const CircleCollider& a, const CircleCollider& b);
CollisionResult AABBvsCircle(const AABB& box, const CircleCollider& circle);
