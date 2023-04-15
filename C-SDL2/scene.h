#ifndef SCENE_H
#define SCENE_H

#include "main.h"

struct Scene {
    SDL_Renderer *renderer;
    SDL_Texture *backgroundsky;
    SDL_Texture *backgroundhills;
    SDL_Texture *background;
    SDL_Rect sky_rect;
    SDL_Rect hills_rect;
    SDL_Rect ground_rect;
    bool error;
};

struct Scene* scene_new(SDL_Renderer *renderer);
void scene_free(struct Scene *this);
bool scene_draw(struct Scene *this);

#endif // SHOP_H