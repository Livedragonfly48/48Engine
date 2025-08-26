#pragma once
#include "../Math/Vec2.h"

/// <summary>
/// Tipos de colliders disponibles.
/// </summary>
enum class ColliderType
{
    AABB,    ///< Caja alineada a los ejes
    Circle   ///< Circulo
};

/// <summary>
/// Clase base para todos los colliders.
/// </summary>
struct Collider
{
    /// <summary>Tipo del collider.</summary>
    ColliderType type;

    /// <summary>Constructor que recibe el tipo de collider.</summary>
    /// <param name="t">Tipo del collider.</param>
    Collider(ColliderType t) : type(t) {}

    /// <summary>Destructor virtual.</summary>
    virtual ~Collider() {}
};

/// <summary>
/// Collider de tipo AABB (Axis-Aligned Bounding Box).
/// </summary>
struct AABB : public Collider
{
    /// <summary>Centro de la caja.</summary>
    Vec2 center;

    /// <summary>Mitad del tamaño de la caja en cada eje.</summary>
    Vec2 halfSize;

    /// <summary>Constructor por defecto, inicializa todo en cero.</summary>
    AABB() : Collider(ColliderType::AABB), center(0.0f, 0.0f), halfSize(0.0f, 0.0f) {}

    /// <summary>Constructor que recibe centro y mitad del tamaño.</summary>
    /// <param name="c">Centro de la caja.</param>
    /// <param name="hs">Mitad del tamaño de la caja.</param>
    AABB(const Vec2& c, const Vec2& hs) : Collider(ColliderType::AABB), center(c), halfSize(hs) {}

    /// <summary>Obtiene la esquina minima (inferior izquierda) de la caja.</summary>
    /// <returns>Vector con coordenadas minimas.</returns>
    Vec2 Min() const { return center - halfSize; }

    /// <summary>Obtiene la esquina maxima (superior derecha) de la caja.</summary>
    /// <returns>Vector con coordenadas maximas.</returns>
    Vec2 Max() const { return center + halfSize; }
};

/// <summary>
/// Collider de tipo circulo.
/// </summary>
struct CircleCollider : public Collider
{
    /// <summary>Centro del circulo.</summary>
    Vec2 center;

    /// <summary>Radio del circulo.</summary>
    float radius;

    /// <summary>Constructor por defecto, inicializa todo en cero.</summary>
    CircleCollider() : Collider(ColliderType::Circle), center(0.0f, 0.0f), radius(0.0f) {}

    /// <summary>Constructor que recibe centro y radio.</summary>
    /// <param name="c">Centro del circulo.</param>
    /// <param name="r">Radio del circulo.</param>
    CircleCollider(const Vec2& c, float r) : Collider(ColliderType::Circle), center(c), radius(r) {}
};
