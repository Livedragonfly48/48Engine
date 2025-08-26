#include "Raycast.h"
#include "../Math/MathUtils.h"

/// <summary>
/// Realiza la interseccion entre un rayo y un segmento de linea.
/// </summary>
/// <param name="ray">Rayo a evaluar.</param>
/// <param name="segment">Segmento de linea a evaluar.</param>
/// <returns>
/// Resultado del raycast indicando si hubo colision, el punto de impacto y la distancia desde el origen.
/// </returns>
RaycastResult Raycast(const Ray& ray, const LineSegment& segment)
{
    RaycastResult result;

    /// <summary>Punto de inicio del rayo.</summary>
    Vec2 p = ray.origin;

    /// <summary>Direccion del rayo.</summary>
    Vec2 r = ray.direction;

    /// <summary>Punto inicial del segmento de linea.</summary>
    Vec2 q = segment.start;

    /// <summary>Vector que representa el segmento.</summary>
    Vec2 s = segment.end - segment.start;

    /// <summary>Producto cruzado entre r y s.</summary>
    float rxs = r.x * s.y - r.y * s.x;
    if (rxs == 0.0f)
    {
        // Rayos paralelos, no hay interseccion
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
