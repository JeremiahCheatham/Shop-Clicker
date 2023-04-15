#ifndef SHOP_H
#define SHOP_H

#include "main.h"

struct Shop {
    SDL_Renderer *renderer;
    SDL_Texture *level1;
    SDL_Texture *level2;
    SDL_Texture *level3;
    SDL_Texture *level4;
    SDL_Texture *level5;
    SDL_Texture *level6;
    SDL_Rect rect;
    bool error;
};

struct Shop* shop_new(SDL_Renderer *renderer);
void shop_free(struct Shop *this);
bool shop_draw(struct Shop *this, Uint8 level);

#endif // SHOP_H