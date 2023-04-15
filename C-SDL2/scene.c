// Included header files.
#include "scene.h"

struct Scene* scene_new(SDL_Renderer *renderer) {
    struct Scene *this = calloc(1, sizeof(struct Scene));
    if (!this) {
        fprintf(stderr, "Error in malloc of scene!\n");
        return this;
    }

    this->renderer = renderer;
    this->error = true;

    this->backgroundsky = IMG_LoadTexture(this->renderer, "images/background.png");
    if (!this->backgroundsky) {
        fprintf(stderr, "Error creating a texture: %s\n", SDL_GetError());
        return false;
    }

    if (SDL_QueryTexture(this->backgroundsky, NULL, NULL, &this->sky_rect.w, &this->sky_rect.h)) {
        fprintf(stderr, "Error while querying texture: %s\n", SDL_GetError());
        return false;
    }
    this->sky_rect.w *= 10;
    this->sky_rect.h *= 10;

    this->backgroundhills = IMG_LoadTexture(this->renderer, "images/terrain.png");
    if (!this->backgroundhills) {
        fprintf(stderr, "Error creating a texture: %s\n", SDL_GetError());
        return false;
    }

    if (SDL_QueryTexture(this->backgroundhills, NULL, NULL, &this->hills_rect.w, &this->hills_rect.h)) {
        fprintf(stderr, "Error while querying texture: %s\n", SDL_GetError());
        return false;
    }
    this->hills_rect.w *= 10;
    this->hills_rect.h *= 10;
    this->hills_rect.y = 400;

    this->background = IMG_LoadTexture(this->renderer, "images/ground.png");
    if (!this->background) {
        fprintf(stderr, "Error creating a texture: %s\n", SDL_GetError());
        return false;
    }

    if (SDL_QueryTexture(this->background, NULL, NULL, &this->ground_rect.w, &this->ground_rect.h)) {
        fprintf(stderr, "Error while querying texture: %s\n", SDL_GetError());
        return false;
    }
    this->ground_rect.w *= 10;
    this->ground_rect.h *= 10;
    this->ground_rect.y = 500;

    this->error = false;
    return this;
}

void scene_free(struct Scene *this) {
    SDL_DestroyTexture(this->backgroundsky);
    SDL_DestroyTexture(this->backgroundhills);
    SDL_DestroyTexture(this->background);
    free(this);
}

bool scene_draw(struct Scene *this) {
    if (SDL_RenderCopy(this->renderer, this->backgroundsky, NULL, &this->sky_rect)) {
        fprintf(stderr, "Error while rendering texture: %s\n", SDL_GetError());
        return false;
    }

    if (SDL_RenderCopy(this->renderer, this->backgroundhills, NULL, &this->hills_rect)) {
        fprintf(stderr, "Error while rendering texture: %s\n", SDL_GetError());
        return false;
    }

    if (SDL_RenderCopy(this->renderer, this->background, NULL, &this->ground_rect)) {
        fprintf(stderr, "Error while rendering texture: %s\n", SDL_GetError());
        return false;
    }

    return true;
}