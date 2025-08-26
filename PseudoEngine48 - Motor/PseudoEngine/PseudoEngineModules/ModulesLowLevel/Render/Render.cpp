#include "Render.h"
#include <SDL_image.h>
#include <iostream>

/// <summary>
/// Constructor de Render.
/// Inicializa punteros de window y renderer a nullptr.
/// </summary>
Render::Render()
    : window(nullptr), renderer(nullptr)
{
}

/// <summary>
/// Destructor de Render.
/// Llama a destroy() para liberar recursos.
/// </summary>
Render::~Render()
{
    destroy();
}

/// <summary>
/// Inicializa SDL y SDL_image, crea la ventana y el renderer.
/// </summary>
/// <param name="title">Titulo de la ventana.</param>
/// <param name="width">Ancho de la ventana.</param>
/// <param name="height">Alto de la ventana.</param>
/// <returns>True si la inicializacion fue exitosa, false en caso contrario.</returns>
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

    // OPCIONAL: fondo negro
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    return true;
}

/// <summary>
/// Limpia el renderer para un nuevo frame.
/// </summary>
void Render::clear()
{
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(renderer);
}

/// <summary>
/// Presenta el contenido del renderer en pantalla.
/// </summary>
void Render::present()
{
    SDL_RenderPresent(renderer);
}

/// <summary>
/// Libera recursos de SDL y SDL_image.
/// </summary>
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

/// <summary>
/// Carga una imagen desde archivo y la convierte en textura de SDL.
/// </summary>
/// <param name="filePath">Ruta del archivo de imagen.</param>
/// <returns>Puntero a SDL_Texture si la carga fue exitosa, nullptr en caso contrario.</returns>
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

/// <summary>
/// Dibuja la textura en la posicion y tamaño indicados.
/// </summary>
/// <param name="texture">Textura a dibujar.</param>
/// <param name="x">Coordenada X de la esquina superior izquierda.</param>
/// <param name="y">Coordenada Y de la esquina superior izquierda.</param>
/// <param name="w">Ancho de la textura.</param>
/// <param name="h">Alto de la textura.</param>
void Render::drawTexture(SDL_Texture* texture, int x, int y, int w, int h)
{
    if (!texture) return;

    SDL_Rect dstRect = { x, y, w, h };
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
}
