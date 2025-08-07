#include "PseudoEngineModules/ModulesLowLevel/Math/Vec2.h"
#include "PseudoEngineModules/ModulesLowLevel/Input/Input.h"
#include "PseudoEngineModules/ModulesLowLevel/Render/Render.h"
#include "PseudoEngineModules/ModulesLowLevel/Physics/PhysicsBody.h"
#include "PseudoEngineModules/ModulesLowLevel/Physics/PhysicsSystem.h"
#include "PseudoEngineModules/ModulesLowLevel/Collision/Collider.h"
#include "PseudoEngineModules/ModulesLowLevel/Collision/CollisionSystem.h"

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <iostream>

const int WIDTH = 800;
const int HEIGHT = 600;
bool running = true;

Render renderer;
PhysicsSystem physicsSystem;

PhysicsBody player(ColliderType::AABB);
PhysicsBody dynamicBox(ColliderType::AABB);
PhysicsBody triggerBody(ColliderType::AABB);

AABB groundLeft(Vec2(150, 550), Vec2(200, 20));
AABB groundRight(Vec2(550, 550), Vec2(200, 20));

bool triggerActive = false;

void drawAABB(const AABB& aabb, Uint8 r, Uint8 g, Uint8 b)
{
    SDL_Rect rect;
    Vec2 min = aabb.Min();
    rect.x = (int)min.x;
    rect.y = (int)min.y;
    rect.w = (int)(aabb.halfSize.x * 2);
    rect.h = (int)(aabb.halfSize.y * 2);
    SDL_SetRenderDrawColor(renderer.getRenderer(), r, g, b, 255);
    SDL_RenderFillRect(renderer.getRenderer(), &rect);
}

void setup()
{
    renderer.init("MiniJuego Trigger", WIDTH, HEIGHT);
    Input::Init();

 
    physicsSystem.staticColliders.push_back(&groundLeft);
    physicsSystem.staticColliders.push_back(&groundRight);

    

    player.position = Vec2(150, 500);
    player.velocity = Vec2(0, 0);
    player.gravityScale = 1.0f;
    player.useGravity = true;
    player.isTrigger = false;
    player.setAABB(player.position, Vec2(15, 15));
    physicsSystem.addBody(&player);



    dynamicBox.position = Vec2(550, 500);
    dynamicBox.velocity = Vec2(0, 0);
    dynamicBox.gravityScale = 0.0f;
    dynamicBox.useGravity = false;
    dynamicBox.isTrigger = false;
    dynamicBox.setAABB(dynamicBox.position, Vec2(15, 15));
    physicsSystem.addBody(&dynamicBox);



    triggerBody.position = Vec2(550, 499);
    triggerBody.velocity = Vec2(0, 0);
    triggerBody.gravityScale = 0.0f;
    triggerBody.useGravity = false;
    triggerBody.isTrigger = true;
    triggerBody.setAABB(triggerBody.position, Vec2(40, 10));
    physicsSystem.addBody(&triggerBody);
}



void handleInput()
{

    Input::ProcessEvents();

    if (Input::IsKeyPressed(SDL_SCANCODE_ESCAPE))
        running = false;

    float speed = 200.0f;

    if (Input::IsKeyHeld(SDL_SCANCODE_A))
        player.velocity.x = -speed;
    else if (Input::IsKeyHeld(SDL_SCANCODE_D))
        player.velocity.x = speed;
    else
        player.velocity.x = 0;


}



void update(float dt)
{
    physicsSystem.update(dt);

    triggerActive = false;
    if (player.triggerEnter || player.triggerStay || dynamicBox.triggerEnter || dynamicBox.triggerStay)
        triggerActive = true;
}




void render()
{
    renderer.clear();

    
    drawAABB(groundLeft, 100, 100, 100);
    drawAABB(groundRight, 100, 100, 100);

  
    drawAABB(player.aabb, 0, 0, 255);

    
    drawAABB(dynamicBox.aabb, 255, 165, 0);


    drawAABB(triggerBody.aabb, 255, 255, 0);


    SDL_Rect indicator;
    indicator.x = WIDTH - 60;
    indicator.y = 20;
    indicator.w = 40;
    indicator.h = 40;
    if (triggerActive)
        SDL_SetRenderDrawColor(renderer.getRenderer(), 0, 255, 0, 255);
    else
        SDL_SetRenderDrawColor(renderer.getRenderer(), 255, 0, 0, 255);
    SDL_RenderFillRect(renderer.getRenderer(), &indicator);

    renderer.present();
}



int main(int argc, char* argv[])
{
    setup();

    Uint32 lastTicks = SDL_GetTicks();

    while (running)
    {
        Uint32 now = SDL_GetTicks();
        float dt = (now - lastTicks) / 1000.0f;
        lastTicks = now;

        handleInput();
        update(dt);
        render();
    }

    renderer.destroy();
    Input::Shutdown();

    return 0;
}
