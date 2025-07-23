#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>

class Input
{
public:
   
    static bool Init();

    
    static void ProcessEvents();

   
    static bool IsKeyPressed(SDL_Scancode key);

    
    static bool IsKeyReleased(SDL_Scancode key);

    
    static bool IsKeyHeld(SDL_Scancode key);

  
    static void Shutdown();

private:
    static const Uint8* currentKeyStates;
    static Uint8* previousKeyStates;
    static int numKeys;
};

#endif 
