#include "CollisionSystem.h"
#include "../Math/MathUtils.h"


CollisionResult AABBvsAABB(const AABB& a, const AABB& b)
{
	CollisionResult result;

	Vec2 delta = b.center - a.center;
	Vec2 overlap = Vec2(
		a.halfSize.x + b.halfSize.x - absf(delta.x),
		a.halfSize.y + b.halfSize.y - absf(delta.y)
	);

	if (overlap.x > 0 && overlap.y > 0)
	{
		result.collided = true;
		if (overlap.x < overlap.y)
		{
			result.penetration = overlap.x;
			result.normal = Vec2(delta.x < 0 ? -1.0f : 1.0f, 0.0f);
		}
		else
		{
			result.penetration = overlap.y;
			result.normal = Vec2(0.0f, delta.y < 0 ? -1.0f : 1.0f);
		}
	}

	return result;
}

CollisionResult CirclevsCircle(const CircleCollider& a, const CircleCollider& b)
{
	CollisionResult result;

	Vec2 delta = b.center - a.center;
	float distSq = delta.lengthSquared();
	float radiusSum = a.radius + b.radius;

	if (distSq <= radiusSum * radiusSum)
	{
		result.collided = true;
		float dist = sqrt_approx(distSq);
		result.penetration = radiusSum - dist;
		result.normal = (dist != 0.0f) ? delta / dist : Vec2(1.0f, 0.0f);
	}

	return result;
}


CollisionResult AABBvsCircle(const AABB& box, const CircleCollider& circle)
{
	CollisionResult result;

	Vec2 closestPoint = Vec2(
		Clamp(circle.center.x, box.Min().x, box.Max().x),
		Clamp(circle.center.y, box.Min().y, box.Max().y)
	);

	Vec2 delta = circle.center - closestPoint;
	float distSq = delta.lengthSquared();

	if (distSq <= circle.radius * circle.radius)
	{
		result.collided = true;
		float dist = sqrt_approx(distSq);
		result.penetration = circle.radius - dist;
		result.normal = (dist != 0.0f) ? delta / dist : Vec2(1.0f, 0.0f);
	}

	return result;
}
