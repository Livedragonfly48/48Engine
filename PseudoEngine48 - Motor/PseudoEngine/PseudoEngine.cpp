#include "PseudoEngineModules/ModulesLowLevel/Math/Vec2.h"
#include "PseudoEngineModules/ModulesLowLevel/Math/MathUtils.h"
#include "PseudoEngineModules/ModulesLowLevel/Input/Input.h"
#include "PseudoEngineModules/ModulesLowLevel/Render/Render.h"
#include "PseudoEngineModules/ModulesLowLevel/Collision/Collider.h"
#include "PseudoEngineModules/ModulesLowLevel/Collision/CollisionSystem.h"

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <iostream>

int main()
{
    Render render;
    if (!render.init("Test AABB Collision", 800, 600))
    {
        std::cerr << "Error inicializando SDL\n";
        return 1;
    }

    if (!Input::Init())
    {
        std::cerr << "Error inicializando Input\n";
        return 1;
    }


    Vec2 playerPos(100.0f, 300.0f);
    Vec2 playerSize(50.0f, 50.0f);
    float playerSpeed = 200.0f;


    Vec2 wallPos(400.0f, 300.0f);
    Vec2 wallSize(100.0f, 100.0f);
    AABB wallBox(wallPos, wallSize * 0.5f);

    Uint32 lastTicks = SDL_GetTicks();
    bool running = true;

    while (running)
    {
        Uint32 currentTicks = SDL_GetTicks();
        float deltaTime = (currentTicks - lastTicks) / 1000.0f;
        lastTicks = currentTicks;

        Input::ProcessEvents();

        if (Input::IsKeyPressed(SDL_SCANCODE_ESCAPE))
            running = false;


        float moveX = 0.0f;
        if (Input::IsKeyHeld(SDL_SCANCODE_A))
            moveX -= playerSpeed * deltaTime;
        if (Input::IsKeyHeld(SDL_SCANCODE_D))
            moveX += playerSpeed * deltaTime;

        Vec2 tentativePos = playerPos + Vec2(moveX, 0.0f);
        AABB tentativeBox(tentativePos, playerSize * 0.5f);


        if (!AABBvsAABB(tentativeBox, wallBox).collided)
        {
            playerPos = tentativePos;
        }


        render.clear();


        SDL_SetRenderDrawColor(render.getRenderer(), 0, 0, 0, 255);
        SDL_RenderClear(render.getRenderer());


        SDL_SetRenderDrawColor(render.getRenderer(), 255, 255, 255, 255);
        SDL_Rect playerRect = {
            int(playerPos.x - playerSize.x * 0.5f),
            int(playerPos.y - playerSize.y * 0.5f),
            int(playerSize.x),
            int(playerSize.y)
        };
        SDL_RenderFillRect(render.getRenderer(), &playerRect);


        SDL_SetRenderDrawColor(render.getRenderer(), 255, 0, 0, 255);
        SDL_Rect wallRect = {
            int(wallPos.x - wallSize.x * 0.5f),
            int(wallPos.y - wallSize.y * 0.5f),
            int(wallSize.x),
            int(wallSize.y)
        };
        SDL_RenderFillRect(render.getRenderer(), &wallRect);

        render.present();

        SDL_Delay(16);
    }

    Input::Shutdown();
    render.destroy();

    return 0;
}