#pragma once
#include "../Math/Vec2.h"
#include "../Collision/CollisionSystem.h"
#include "PhysicsBody.h"
#include "../VectorDynam/MyVector.h"

struct PhysicsSystem
{
    MyVector<PhysicsBody*> bodies;
    MyVector<Collider*> staticColliders; 

    Vec2 globalGravity = Vec2(0.0f, 980.0f);

    void addBody(PhysicsBody* body);
    void removeBody(PhysicsBody* body);

    void update(float deltaTime);

private:
    void checkCollisions();  
};


