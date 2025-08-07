#pragma once
#include "../Math/Vec2.h"

enum class ColliderType
{
    AABB,
    Circle
};

struct Collider
{
    ColliderType type;

    Collider(ColliderType t) : type(t) {}
    virtual ~Collider() {}
};

struct AABB : public Collider
{
    Vec2 center;
    Vec2 halfSize;

    AABB() : Collider(ColliderType::AABB), center(0.0f, 0.0f), halfSize(0.0f, 0.0f) {}
    AABB(const Vec2& c, const Vec2& hs) : Collider(ColliderType::AABB), center(c), halfSize(hs) {}

    Vec2 Min() const { return center - halfSize; }
    Vec2 Max() const { return center + halfSize; }
};

struct CircleCollider : public Collider
{
    Vec2 center;
    float radius;

    CircleCollider() : Collider(ColliderType::Circle), center(0.0f, 0.0f), radius(0.0f) {}
    CircleCollider(const Vec2& c, float r) : Collider(ColliderType::Circle), center(c), radius(r) {}
};
