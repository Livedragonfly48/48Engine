#include <iostream>
#include "Math/Vec2.h"
#include "Math/MathUtils.h"
#include "Raycast/Raycast.h"
#include "Input/Input.h"
#include "Render/Render.h"

#define SDL_MAIN_HANDLED
#include <SDL.h>

const int MAP_WIDTH = 11;
const int MAP_HEIGHT = 11;
const int TILE_SIZE = 48;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


int map[MAP_HEIGHT][MAP_WIDTH] = {
    {1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,1,0,0,0,0,1},
    {1,0,1,1,0,1,0,1,1,0,1},
    {1,0,1,0,0,0,0,0,1,0,1},
    {1,0,1,0,1,1,1,0,1,0,1},
    {1,0,0,0,1,0,1,0,0,0,1},
    {1,1,1,0,1,0,1,1,1,0,1},
    {1,0,0,0,0,0,0,0,1,0,1},
    {1,0,1,1,1,1,1,0,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1},
};

float degToRad(float deg) {
    return deg * M_PI / 180.0f;
}

int main()
{
    Render render;
    if (!render.init("Prueba con todos los modulos para Pres", SCREEN_WIDTH, SCREEN_HEIGHT))
    {
        std::cerr << "Error al iniciar SDL\n";
        return 1;
    }

    if (!Input::Init())
    {
        std::cerr << "Error al iniciar Input\n";
        return 1;
    }

    // Cargar texturas
    SDL_Texture* wallTexture = render.loadTexture("D:\\Personal\\MotorDV\\PseudoEngine\\Render\\Textures\\Pared48.png");
    SDL_Texture* floorTexture = render.loadTexture("D:\\Personal\\MotorDV\\PseudoEngine\\Render\\Textures\\Suelo48.png");
    if (!wallTexture || !floorTexture)
    {
        std::cerr << "Error al cargar texturas\n";
        return 1;
    }

    Vec2 playerPos(3.0f, 3.0f);
    float playerAngle = 0.0f;
    float fov = degToRad(60.0f);
    float moveSpeed = 3.0f;
    float rotSpeed = 2.0f;

    Uint32 lastTime = SDL_GetTicks();
    bool running = true;

    while (running)
    {
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        Input::ProcessEvents();
        if (Input::IsKeyPressed(SDL_SCANCODE_ESCAPE))
            running = false;

        if (Input::IsKeyHeld(SDL_SCANCODE_W))
        {
            Vec2 newPos = playerPos + Vec2(std::cos(playerAngle), std::sin(playerAngle)) * moveSpeed * deltaTime;
            if (map[int(newPos.y)][int(newPos.x)] == 0) playerPos = newPos;
        }
        if (Input::IsKeyHeld(SDL_SCANCODE_S))
        {
            Vec2 newPos = playerPos - Vec2(std::cos(playerAngle), std::sin(playerAngle)) * moveSpeed * deltaTime;
            if (map[int(newPos.y)][int(newPos.x)] == 0) playerPos = newPos;
        }
        if (Input::IsKeyHeld(SDL_SCANCODE_A))
            playerAngle -= rotSpeed * deltaTime;
        if (Input::IsKeyHeld(SDL_SCANCODE_D))
            playerAngle += rotSpeed * deltaTime;

        render.clear();

        for (int x = 0; x < SCREEN_WIDTH; ++x)
        {
            float rayAngle = (playerAngle - fov / 2.0f) + (float(x) / SCREEN_WIDTH) * fov;
            Vec2 rayDir(std::cos(rayAngle), std::sin(rayAngle));

            int mapX = int(playerPos.x);
            int mapY = int(playerPos.y);

            float sideDistX, sideDistY;
            float deltaDistX = (rayDir.x == 0) ? 1e30f : std::abs(1 / rayDir.x);
            float deltaDistY = (rayDir.y == 0) ? 1e30f : std::abs(1 / rayDir.y);
            float perpWallDist;

            int stepX, stepY;
            bool hit = false;
            int side;

            if (rayDir.x < 0)
            {
                stepX = -1;
                sideDistX = (playerPos.x - mapX) * deltaDistX;
            }
            else
            {
                stepX = 1;
                sideDistX = (mapX + 1.0f - playerPos.x) * deltaDistX;
            }
            if (rayDir.y < 0)
            {
                stepY = -1;
                sideDistY = (playerPos.y - mapY) * deltaDistY;
            }
            else
            {
                stepY = 1;
                sideDistY = (mapY + 1.0f - playerPos.y) * deltaDistY;
            }

            while (!hit)
            {
                if (sideDistX < sideDistY)
                {
                    sideDistX += deltaDistX;
                    mapX += stepX;
                    side = 0;
                }
                else
                {
                    sideDistY += deltaDistY;
                    mapY += stepY;
                    side = 1;
                }
                if (mapY >= 0 && mapY < MAP_HEIGHT && mapX >= 0 && mapX < MAP_WIDTH)
                {
                    if (map[mapY][mapX] == 1)
                        hit = true;
                }
                else
                {
                    hit = true;
                }
            }

            if (side == 0)
                perpWallDist = (sideDistX - deltaDistX);
            else
                perpWallDist = (sideDistY - deltaDistY);

            int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);
            int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
            if (drawStart < 0) drawStart = 0;
            int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
            if (drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1;

            float wallX;
            if (side == 0)
                wallX = playerPos.y + perpWallDist * rayDir.y;
            else
                wallX = playerPos.x + perpWallDist * rayDir.x;
            wallX -= std::floor(wallX);

            int texWidth = 48;
            int texX = int(wallX * float(texWidth));
            if (side == 0 && rayDir.x > 0) texX = texWidth - texX - 1;
            if (side == 1 && rayDir.y < 0) texX = texWidth - texX - 1;

            SDL_Rect srcRect = { texX, 0, 1, 48 };
            SDL_Rect dstRect = { x, drawStart, 1, drawEnd - drawStart };
            SDL_RenderCopy(render.getRenderer(), wallTexture, &srcRect, &dstRect);

            
            SDL_Rect floorSrc = { 0, 0, 1, 1 };
            SDL_Rect floorDst = { x, drawEnd, 1, SCREEN_HEIGHT - drawEnd };
            SDL_RenderCopy(render.getRenderer(), floorTexture, &floorSrc, &floorDst);
        }

        render.present();
    }

    Input::Shutdown();
    render.destroy();
    return 0;
}
