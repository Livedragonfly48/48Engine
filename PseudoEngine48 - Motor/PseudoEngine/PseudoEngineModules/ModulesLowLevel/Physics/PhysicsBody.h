#pragma once
#include "../Math/Vec2.h"
#include "../Collision/Collider.h"

class PhysicsBody
{

public:
    Vec2 position;
    Vec2 velocity;
    Vec2 acceleration;

    float gravityScale = 1.0f;
    bool useGravity = true;
    bool isTrigger = false;

    ColliderType colliderType;

    
    AABB aabb;
    CircleCollider circle;

    bool triggerEnter = false;
    bool triggerStay = false;
    bool triggerExit = false;


    bool wasCollidingLastFrame = false;
    bool isCurrentlyColliding = false;


public:

    PhysicsBody(ColliderType type)
        : position(0, 0), velocity(0, 0), acceleration(0, 0), colliderType(type)
    {

    }

    void setAABB(const Vec2& center, const Vec2& halfSize)
    {
        aabb = AABB(center, halfSize);
        colliderType = ColliderType::AABB;
        position = center;
    }

    void setCircle(const Vec2& center, float radius)
    {
        circle = CircleCollider(center, radius);
        colliderType = ColliderType::Circle;
        position = center;
    }

    void updateColliderPosition()
    {
        if (colliderType == ColliderType::AABB)
        {
            aabb.center = position;
        }
        else if (colliderType == ColliderType::Circle)
        {
            circle.center = position;
        }
    }
};
