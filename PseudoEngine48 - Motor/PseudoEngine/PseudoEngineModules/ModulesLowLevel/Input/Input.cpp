#include "Input.h"
#include <cstring> 

/// <summary>Estado actual de todas las teclas.</summary>
const Uint8* Input::currentKeyStates = nullptr;
/// <summary>Estado previo de todas las teclas.</summary>
Uint8* Input::previousKeyStates = nullptr;
/// <summary>Numero de teclas en el teclado.</summary>
int Input::numKeys = 0;

/// <summary>
/// Inicializa el sistema de entrada.
/// Obtiene el estado actual del teclado y reserva memoria para el estado previo.
/// </summary>
/// <returns>True si la inicializacion fue exitosa.</returns>
bool Input::Init()
{
    currentKeyStates = SDL_GetKeyboardState(&numKeys);
    if (numKeys <= 0) return false;

    previousKeyStates = new Uint8[numKeys];
    std::memcpy(previousKeyStates, currentKeyStates, numKeys);
    return true;
}

/// <summary>
/// Actualiza el estado de todas las teclas.
/// Debe llamarse cada frame antes de consultar IsKeyPressed/IsKeyReleased/IsKeyHeld.
/// </summary>
void Input::ProcessEvents()
{
    // Copiar el estado previo
    std::memcpy(previousKeyStates, currentKeyStates, numKeys);

    // Actualizar estado actual
    SDL_PumpEvents();
    currentKeyStates = SDL_GetKeyboardState(nullptr);
}

/// <summary>
/// Verifica si una tecla fue presionada en el frame actual.
/// </summary>
/// <param name="key">Tecla a verificar (SDL_Scancode).</param>
/// <returns>True si la tecla fue presionada este frame.</returns>
bool Input::IsKeyPressed(SDL_Scancode key)
{
    return currentKeyStates[key] && !previousKeyStates[key];
}

/// <summary>
/// Verifica si una tecla fue liberada en el frame actual.
/// </summary>
/// <param name="key">Tecla a verificar (SDL_Scancode).</param>
/// <returns>True si la tecla fue liberada este frame.</returns>
bool Input::IsKeyReleased(SDL_Scancode key)
{
    return !currentKeyStates[key] && previousKeyStates[key];
}

/// <summary>
/// Verifica si una tecla esta siendo mantenida presionada.
/// </summary>
/// <param name="key">Tecla a verificar (SDL_Scancode).</param>
/// <returns>True si la tecla esta presionada actualmente.</returns>
bool Input::IsKeyHeld(SDL_Scancode key)
{
    return currentKeyStates[key];
}

/// <summary>
/// Libera los recursos usados por el sistema de entrada.
/// </summary>
void Input::Shutdown()
{
    delete[] previousKeyStates;
    previousKeyStates = nullptr;
}
