#include "Input.h"
#include <cstring> 

const Uint8* Input::currentKeyStates = nullptr;
Uint8* Input::previousKeyStates = nullptr;
int Input::numKeys = 0;

bool Input::Init()
{
    currentKeyStates = SDL_GetKeyboardState(&numKeys);
    if (numKeys <= 0) return false;

    previousKeyStates = new Uint8[numKeys];
    std::memcpy(previousKeyStates, currentKeyStates, numKeys);
    return true;
}

void Input::ProcessEvents()
{
   
    std::memcpy(previousKeyStates, currentKeyStates, numKeys);

    
    SDL_PumpEvents(); 
    currentKeyStates = SDL_GetKeyboardState(nullptr);
}

bool Input::IsKeyPressed(SDL_Scancode key)
{
    return currentKeyStates[key] && !previousKeyStates[key];
}

bool Input::IsKeyReleased(SDL_Scancode key)
{
    return !currentKeyStates[key] && previousKeyStates[key];
}

bool Input::IsKeyHeld(SDL_Scancode key)
{
    return currentKeyStates[key];
}

void Input::Shutdown()
{
    delete[] previousKeyStates;
    previousKeyStates = nullptr;
}
