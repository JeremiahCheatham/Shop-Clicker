#ifndef SHOP_H
#define SHOP_H

#include "main.h"

class Shop {
public:
    Shop(std::shared_ptr<SDL_Renderer> renderer);

    void draw(unsigned int level);

private:
    std::shared_ptr<SDL_Renderer> renderer;
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> level1;
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> level2;
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> level3;
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> level4;
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> level5;
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> level6;
    SDL_Rect rect;
};

#endif // SHOP_H