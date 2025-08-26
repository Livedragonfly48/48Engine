#ifndef RENDER_H
#define RENDER_H

#include <SDL.h>
#include <string>

/// <summary>
/// Clase que maneja la renderizacion usando SDL.
/// Permite inicializar ventana, dibujar texturas y limpiar/presentar frames.
/// </summary>
class Render
{
public:
    /// <summary>Constructor de la clase Render.</summary>
    Render();

    /// <summary>Destructor de la clase Render.</summary>
    ~Render();

    /// <summary>
    /// Inicializa la ventana y el renderer de SDL.
    /// </summary>
    /// <param name="title">Titulo de la ventana.</param>
    /// <param name="width">Ancho de la ventana.</param>
    /// <param name="height">Alto de la ventana.</param>
    /// <returns>True si la inicializacion fue exitosa.</returns>
    bool init(const char* title, int width, int height);

    /// <summary>Limpia el renderer (preparandolo para dibujar un nuevo frame).</summary>
    void clear();

    /// <summary>Muestra en pantalla todo lo que fue dibujado desde el ultimo clear.</summary>
    void present();

    /// <summary>Libera los recursos de SDL (window y renderer).</summary>
    void destroy();

    /// <summary>
    /// Carga una textura desde un archivo.
    /// </summary>
    /// <param name="filePath">Ruta del archivo de la textura.</param>
    /// <returns>Puntero a SDL_Texture si la carga fue exitosa, nullptr en caso contrario.</returns>
    SDL_Texture* loadTexture(const std::string& filePath);

    /// <summary>Dibuja una textura en la pantalla en la posicion y tamaño especificados.</summary>
    /// <param name="texture">Textura a dibujar.</param>
    /// <param name="x">Coordenada X de la esquina superior izquierda.</param>
    /// <param name="y">Coordenada Y de la esquina superior izquierda.</param>
    /// <param name="w">Ancho de la textura.</param>
    /// <param name="h">Alto de la textura.</param>
    void drawTexture(SDL_Texture* texture, int x, int y, int w, int h);

    /// <summary>Obtiene el puntero al renderer de SDL.</summary>
    /// <returns>Puntero a SDL_Renderer.</returns>
    SDL_Renderer* getRenderer() const { return renderer; }

private:
    SDL_Window* window;    ///< Ventana de SDL
    SDL_Renderer* renderer;///< Renderer de SDL
};

#endif // RENDER_H
