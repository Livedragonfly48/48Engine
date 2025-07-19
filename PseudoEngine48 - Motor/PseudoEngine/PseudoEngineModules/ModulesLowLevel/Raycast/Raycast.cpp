#include "Raycast.h"
#include "../Math/MathUtils.h"

RaycastResult Raycast(const Ray& ray, const LineSegment& segment)
{
	RaycastResult result;

	Vec2 p = ray.origin;
	Vec2 r = ray.direction;
	Vec2 q = segment.start;
	Vec2 s = segment.end - segment.start;

	float rxs = r.x * s.y - r.y * s.x;
	if (rxs == 0.0f)
	{
		
		return result;
	}

	Vec2 qp = q - p;
	float t = (qp.x * s.y - qp.y * s.x) / rxs;
	float u = (qp.x * r.y - qp.y * r.x) / rxs;

	if (t >= 0 && u >= 0 && u <= 1)
	{
		result.hit = true;
		result.point = p + r * t;
		result.distance = t;
	}

	return result;
}
