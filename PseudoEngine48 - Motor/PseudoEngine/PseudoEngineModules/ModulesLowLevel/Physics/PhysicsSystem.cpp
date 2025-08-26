#include "PhysicsSystem.h"
#include "../Collision/Collider.h"
#include "../Collision/CollisionSystem.h"
#include "../Math/Vec2.h"

/// <summary>
/// Agrega un cuerpo dinamico al sistema de fisicas.
/// </summary>
/// <param name="body">Puntero al cuerpo fisico a agregar.</param>
void PhysicsSystem::addBody(PhysicsBody* body)
{
    bodies.push_back(body);
}

/// <summary>
/// Elimina un cuerpo dinamico del sistema de fisicas.
/// </summary>
/// <param name="body">Puntero al cuerpo fisico a eliminar.</param>
void PhysicsSystem::removeBody(PhysicsBody* body)
{
    for (size_t i = 0; i < bodies.getSize(); ++i)
    {
        if (bodies[i] == body)
        {
            bodies.erase(i);
            break;
        }
    }
}

/// <summary>
/// Actualiza todos los cuerpos dinamicos, aplica gravedad y mueve los cuerpos.
/// Luego verifica colisiones entre cuerpos dinamicos y colliders estaticos.
/// </summary>
/// <param name="deltaTime">Tiempo transcurrido desde el ultimo frame (en segundos).</param>
void PhysicsSystem::update(float deltaTime)
{
    for (size_t i = 0; i < bodies.getSize(); ++i)
    {
        PhysicsBody* body = bodies[i];

        body->triggerEnter = false;
        body->triggerExit = false;
        body->isCurrentlyColliding = false;

        if (body->useGravity)
            body->acceleration = globalGravity * body->gravityScale;
        else
            body->acceleration = Vec2(0, 0);

        body->velocity += body->acceleration * deltaTime;
        body->position += body->velocity * deltaTime;
        body->updateColliderPosition();
    }

    checkCollisions();

    for (size_t i = 0; i < bodies.getSize(); ++i)
    {
        PhysicsBody* body = bodies[i];
        body->wasCollidingLastFrame = body->isCurrentlyColliding;
    }
}

/// <summary>
/// Verifica colisiones entre todos los cuerpos dinamicos y colliders estaticos.
/// Maneja triggers y ajuste de posiciones/velocidades de los cuerpos.
/// </summary>
void PhysicsSystem::checkCollisions()
{
    // Colisiones entre cuerpos dinamicos
    for (size_t i = 0; i < bodies.getSize(); ++i)
    {
        PhysicsBody* a = bodies[i];
        for (size_t j = i + 1; j < bodies.getSize(); ++j)
        {
            PhysicsBody* b = bodies[j];
            CollisionResult res;
            bool collided = false;

            if (a->colliderType == ColliderType::AABB && b->colliderType == ColliderType::AABB)
                res = AABBvsAABB(a->aabb, b->aabb);
            else if (a->colliderType == ColliderType::Circle && b->colliderType == ColliderType::Circle)
                res = CirclevsCircle(a->circle, b->circle);
            else if (a->colliderType == ColliderType::AABB && b->colliderType == ColliderType::Circle)
                res = AABBvsCircle(a->aabb, b->circle);
            else if (a->colliderType == ColliderType::Circle && b->colliderType == ColliderType::AABB)
                res = AABBvsCircle(b->aabb, a->circle);
            else
                continue;

            collided = res.collided;

            if (a->isTrigger || b->isTrigger)
            {
                if (collided)
                {
                    if (!a->wasCollidingLastFrame)
                        a->triggerEnter = true;
                    a->triggerStay = true;

                    if (!b->wasCollidingLastFrame)
                        b->triggerEnter = true;
                    b->triggerStay = true;
                }
                else
                {
                    if (a->wasCollidingLastFrame)
                        a->triggerExit = true;
                    if (b->wasCollidingLastFrame)
                        b->triggerExit = true;

                    a->triggerStay = false;
                    b->triggerStay = false;
                }

                a->isCurrentlyColliding = a->isCurrentlyColliding || collided;
                b->isCurrentlyColliding = b->isCurrentlyColliding || collided;
            }
            else
            {
                if (collided)
                {
                    a->position -= res.normal * res.penetration;
                    a->updateColliderPosition();

                    if (a->useGravity && !b->useGravity)
                        b->velocity += a->velocity * 0.5f;
                    else if (!a->useGravity && b->useGravity)
                        a->velocity += b->velocity * 0.5f;
                    else
                    {
                        a->velocity *= 0.8f;
                        b->velocity *= 0.8f;
                    }
                }
            }
        }
    }

    // Colisiones con colliders estaticos
    for (size_t i = 0; i < bodies.getSize(); ++i)
    {
        PhysicsBody* body = bodies[i];

        for (size_t j = 0; j < staticColliders.getSize(); ++j)
        {
            Collider* col = staticColliders[j];
            CollisionResult res;
            bool collided = false;

            if (body->colliderType == ColliderType::AABB && col->type == ColliderType::AABB)
                res = AABBvsAABB(body->aabb, *(AABB*)col);
            else if (body->colliderType == ColliderType::Circle && col->type == ColliderType::Circle)
                res = CirclevsCircle(body->circle, *(CircleCollider*)col);
            else if (body->colliderType == ColliderType::AABB && col->type == ColliderType::Circle)
                res = AABBvsCircle(body->aabb, *(CircleCollider*)col);
            else if (body->colliderType == ColliderType::Circle && col->type == ColliderType::AABB)
                res = AABBvsCircle(*(AABB*)col, body->circle);
            else
                continue;

            collided = res.collided;

            if (collided)
            {
                body->position -= res.normal * res.penetration;
                body->updateColliderPosition();
                body->velocity = Vec2(0, 0);
            }
        }
    }
}
