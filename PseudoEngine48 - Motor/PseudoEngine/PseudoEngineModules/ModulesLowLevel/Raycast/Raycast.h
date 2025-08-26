#pragma once
#include "../Math/Vec2.h"

/// <summary>
/// Representa un rayo en 2D.
/// </summary>
struct Ray
{
    /// <summary>Origen del rayo.</summary>
    Vec2 origin;

    /// <summary>Direccion del rayo.</summary>
    Vec2 direction;
};

/// <summary>
/// Representa un segmento de linea en 2D.
/// </summary>
struct LineSegment
{
    /// <summary>Punto inicial del segmento.</summary>
    Vec2 start;

    /// <summary>Punto final del segmento.</summary>
    Vec2 end;
};

/// <summary>
/// Resultado de un raycast.
/// </summary>
struct RaycastResult
{
    /// <summary>Indica si hubo colision.</summary>
    bool hit = false;

    /// <summary>Punto de impacto, si hubo colision.</summary>
    Vec2 point = Vec2(0.0f, 0.0f);

    /// <summary>Distancia desde el origen hasta el punto de impacto.</summary>
    float distance = 0.0f;
};

/// <summary>
/// Calcula la interseccion entre un rayo y un segmento de linea.
/// </summary>
/// <param name="ray">Rayo a evaluar.</param>
/// <param name="segment">Segmento de linea a evaluar.</param>
/// <returns>Resultado del raycast indicando si hubo colision, punto y distancia.</returns>
RaycastResult Raycast(const Ray& ray, const LineSegment& segment);
