#ifndef UPGRADE_H
#define UPGRADE_H

#include "main.h"

struct Upgrade {
    SDL_Renderer *renderer;
    SDL_Texture *upgrade1;
    SDL_Texture *upgrade2;
    SDL_Texture *upgrade3;
    SDL_Texture *upgrade4;
    SDL_Texture *upgrade5;
    SDL_Rect rect;
    bool error;
};

struct Upgrade* upgrade_new(SDL_Renderer *renderer);
void upgrade_free(struct Upgrade *this);
bool upgrade_draw(struct Upgrade *this, Uint8 level);

#endif // SHOP_H