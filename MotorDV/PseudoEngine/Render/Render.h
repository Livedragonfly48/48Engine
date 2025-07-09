#ifndef RENDER_H
#define RENDER_H

#include <SDL.h>
#include <string>

class Render
{
public:
    Render();
    ~Render();

    bool init(const char* title, int width, int height);
    void clear();
    void present();
    void destroy();

    SDL_Texture* loadTexture(const std::string& filePath);

    void drawTexture(SDL_Texture* texture, int x, int y, int w, int h);

    SDL_Renderer* getRenderer() const { return renderer; }

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif // RENDER_H
