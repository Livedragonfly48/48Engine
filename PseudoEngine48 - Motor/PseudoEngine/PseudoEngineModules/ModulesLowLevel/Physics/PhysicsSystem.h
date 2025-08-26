#pragma once
#include "../Math/Vec2.h"
#include "../Collision/CollisionSystem.h"
#include "PhysicsBody.h"
#include "../VectorDynam/MyVector.h"

/// <summary>
/// Sistema de fisicas que maneja cuerpos dinamicos, colisiones y gravedad global.
/// </summary>
struct PhysicsSystem
{
    /// <summary>Lista de cuerpos fisicos que se actualizan cada frame.</summary>
    MyVector<PhysicsBody*> bodies;

    /// <summary>Lista de colliders estaticos que solo se usan para detectar colisiones.</summary>
    MyVector<Collider*> staticColliders;

    /// <summary>Gravedad global aplicada a los cuerpos que usan gravedad.</summary>
    Vec2 globalGravity = Vec2(0.0f, 980.0f);

    /// <summary>Agrega un cuerpo al sistema de fisicas.</summary>
    /// <param name="body">Puntero al cuerpo fisico a agregar.</param>
    void addBody(PhysicsBody* body);

    /// <summary>Elimina un cuerpo del sistema de fisicas.</summary>
    /// <param name="body">Puntero al cuerpo fisico a eliminar.</param>
    void removeBody(PhysicsBody* body);

    /// <summary>Actualiza la simulacion de fisicas, movimientos y colisiones.</summary>
    /// <param name="deltaTime">Tiempo transcurrido desde el ultimo frame (en segundos).</param>
    void update(float deltaTime);

private:
    /// <summary>Verifica colisiones entre todos los cuerpos dinamicos y colliders estaticos.</summary>
    void checkCollisions();
};
