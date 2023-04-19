#ifndef UPGRADE_H
#define UPGRADE_H

#include "main.h"

class Upgrade {
public:
    Upgrade(std::shared_ptr<SDL_Renderer> renderer);

    void draw(unsigned int upgrade);

private:
    std::shared_ptr<SDL_Renderer> renderer;
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> upgrade1;
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> upgrade2;
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> upgrade3;
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> upgrade4;
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> upgrade5;
    SDL_Rect rect;
};

#endif // UPGRADE_H