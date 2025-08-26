#pragma once
#include "../Math/Vec2.h"
#include "../Collision/Collider.h"

/// <summary>
/// Representa un cuerpo fisico con propiedades de movimiento, gravedad y colisiones.
/// </summary>
class PhysicsBody
{

public:
    /// <summary>Posicion actual del cuerpo.</summary>
    Vec2 position;

    /// <summary>Velocidad actual del cuerpo.</summary>
    Vec2 velocity;

    /// <summary>Aceleracion actual del cuerpo.</summary>
    Vec2 acceleration;

    /// <summary>Factor de gravedad aplicado.</summary>
    float gravityScale = 1.0f;

    /// <summary>Indica si el cuerpo usa gravedad.</summary>
    bool useGravity = true;

    /// <summary>Indica si el cuerpo es un trigger (solo detecta colisiones sin reaccion fisica).</summary>
    bool isTrigger = false;

    /// <summary>Tipo de collider actual.</summary>
    ColliderType colliderType;

    /// <summary>Collider tipo AABB.</summary>
    AABB aabb;

    /// <summary>Collider tipo circulo.</summary>
    CircleCollider circle;

    /// <summary>Indica si ocurrio triggerEnter.</summary>
    bool triggerEnter = false;

    /// <summary>Indica si el cuerpo sigue colisionando.</summary>
    bool triggerStay = false;

    /// <summary>Indica si ocurrio triggerExit.</summary>
    bool triggerExit = false;

    /// <summary>Registro de si estaba colisionando en el frame anterior.</summary>
    bool wasCollidingLastFrame = false;

    /// <summary>Indica si esta colisionando actualmente.</summary>
    bool isCurrentlyColliding = false;

public:

    /// <summary>
    /// Constructor que inicializa un PhysicsBody con un tipo de collider.
    /// </summary>
    /// <param name="type">Tipo de collider: AABB o Circle.</param>
    PhysicsBody(ColliderType type)
        : position(0, 0), velocity(0, 0), acceleration(0, 0), colliderType(type)
    {

    }

    /// <summary>
    /// Configura el collider como AABB y posiciona el cuerpo.
    /// </summary>
    /// <param name="center">Centro del AABB.</param>
    /// <param name="halfSize">Mitad del tamaño del AABB.</param>
    void setAABB(const Vec2& center, const Vec2& halfSize)
    {
        aabb = AABB(center, halfSize);
        colliderType = ColliderType::AABB;
        position = center;
    }

    /// <summary>
    /// Configura el collider como Circle y posiciona el cuerpo.
    /// </summary>
    /// <param name="center">Centro del circulo.</param>
    /// <param name="radius">Radio del circulo.</param>
    void setCircle(const Vec2& center, float radius)
    {
        circle = CircleCollider(center, radius);
        colliderType = ColliderType::Circle;
        position = center;
    }

    /// <summary>
    /// Actualiza la posicion del collider segun la posicion actual del cuerpo.
    /// </summary>
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
