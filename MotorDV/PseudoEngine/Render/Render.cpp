#include "Render.h"
#include <SDL_image.h>
#include <iostream>

Render::Render()
    : window(nullptr), renderer(nullptr)
{
}

Render::~Render()
{
    destroy();
}

bool Render::init(const char* title, int width, int height)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "Error al inicializar SDL: " << SDL_GetError() << "\n";
        return false;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        std::cout << "Error al inicializar SDL_image: " << IMG_GetError() << "\n";
        return false;
    }

    window = SDL_CreateWindow(title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_SHOWN);

    if (!window)
    {
        std::cout << "Error al crear ventana: " << SDL_GetError() << "\n";
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        std::cout << "Error al crear renderer: " << SDL_GetError() << "\n";
        return false;
    }

    //OPCIONAL FONDO NEGRO
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    return true;
}

void Render::clear()
{
    SDL_RenderClear(renderer);
}

void Render::present()
{
    SDL_RenderPresent(renderer);
}

void Render::destroy()
{
    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    IMG_Quit();
    SDL_Quit();
}

SDL_Texture* Render::loadTexture(const std::string& filePath)
{
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (!surface)
    {
        std::cout << "Error cargando imagen " << filePath << ": " << IMG_GetError() << "\n";
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture)
    {
        std::cout << "Error creando textura desde superficie: " << SDL_GetError() << "\n";
        return nullptr;
    }

    return texture;
}

void Render::drawTexture(SDL_Texture* texture, int x, int y, int w, int h)
{
    if (!texture) return;

    SDL_Rect dstRect = { x, y, w, h };
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
}
