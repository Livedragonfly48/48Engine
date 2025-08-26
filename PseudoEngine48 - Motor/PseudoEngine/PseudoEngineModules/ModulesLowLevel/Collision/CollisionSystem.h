#pragma once
#include "Collider.h"

/// <summary>
/// Resultado de una colision entre dos colliders.
/// </summary>
struct CollisionResult
{
    /// <summary>Indica si hubo colision.</summary>
    bool collided = false;

    /// <summary>Normal de la colision (vector unitario).</summary>
    Vec2 normal = Vec2(0.0f, 0.0f);

    /// <summary>Profundidad de penetracion en la colision.</summary>
    float penetration = 0.0f;
};

/// <summary>
/// Detecta colision entre dos AABBs.
/// </summary>
/// <param name="a">Primer AABB.</param>
/// <param name="b">Segundo AABB.</param>
/// <returns>Resultado de la colision incluyendo normal y penetracion.</returns>
CollisionResult AABBvsAABB(const AABB& a, const AABB& b);

/// <summary>
/// Detecta colision entre dos circulos.
/// </summary>
/// <param name="a">Primer circulo.</param>
/// <param name="b">Segundo circulo.</param>
/// <returns>Resultado de la colision incluyendo normal y penetracion.</returns>
CollisionResult CirclevsCircle(const CircleCollider& a, const CircleCollider& b);

/// <summary>
/// Detecta colision entre un AABB y un circulo.
/// </summary>
/// <param name="box">Caja AABB.</param>
/// <param name="circle">Circulo.</param>
/// <returns>Resultado de la colision incluyendo normal y penetracion.</returns>
CollisionResult AABBvsCircle(const AABB& box, const CircleCollider& circle);
