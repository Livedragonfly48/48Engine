#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>

/// <summary>
/// Clase estatica para manejo de entrada de teclado usando SDL.
/// </summary>
class Input
{
public:

    /// <summary>
    /// Inicializa el sistema de entrada y obtiene el estado actual del teclado.
    /// </summary>
    /// <returns>True si la inicializacion fue exitosa.</returns>
    static bool Init();


    /// <summary>
    /// Procesa los eventos de SDL y actualiza el estado del teclado.
    /// Debe llamarse cada frame antes de consultar el estado de las teclas.
    /// </summary>
    static void ProcessEvents();


    /// <summary>
    /// Verifica si una tecla fue presionada en el frame actual.
    /// </summary>
    /// <param name="key">Tecla a verificar (SDL_Scancode).</param>
    /// <returns>True si la tecla fue presionada este frame.</returns>
    static bool IsKeyPressed(SDL_Scancode key);


    /// <summary>
    /// Verifica si una tecla fue liberada en el frame actual.
    /// </summary>
    /// <param name="key">Tecla a verificar (SDL_Scancode).</param>
    /// <returns>True si la tecla fue liberada este frame.</returns>
    static bool IsKeyReleased(SDL_Scancode key);


    /// <summary>
    /// Verifica si una tecla esta siendo mantenida presionada.
    /// </summary>
    /// <param name="key">Tecla a verificar (SDL_Scancode).</param>
    /// <returns>True si la tecla esta presionada actualmente.</returns>
    static bool IsKeyHeld(SDL_Scancode key);


    /// <summary>
    /// Libera los recursos usados por el sistema de entrada.
    /// </summary>
    static void Shutdown();

private:
    /// <summary>Estado actual de todas las teclas.</summary>
    static const Uint8* currentKeyStates;
    /// <summary>Estado previo de todas las teclas.</summary>
    static Uint8* previousKeyStates;
    /// <summary>Numero de teclas en el teclado.</summary>
    static int numKeys;
};

#endif
