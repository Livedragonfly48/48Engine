#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>

class Input
{
public:
    // Inicializa el sistema de entrada
    static bool Init();

    // Procesa todos los eventos de entrada (debe llamarse cada frame)
    static void ProcessEvents();

    // Devuelve true si la tecla fue presionada este frame
    static bool IsKeyPressed(SDL_Scancode key);

    // Devuelve true si la tecla fue soltada este frame
    static bool IsKeyReleased(SDL_Scancode key);

    // Devuelve true si la tecla está siendo sostenida
    static bool IsKeyHeld(SDL_Scancode key);

    // Libera memoria utilizada
    static void Shutdown();

private:
    static const Uint8* currentKeyStates;
    static Uint8* previousKeyStates;
    static int numKeys;
};

#endif // INPUT_H
