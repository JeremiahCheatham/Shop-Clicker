// Included header files.
#include "upgrade.h"

struct Upgrade* upgrade_new(SDL_Renderer *renderer) {
    struct Upgrade *this = calloc(1, sizeof(struct Upgrade));
    if (!this) {
        fprintf(stderr, "Error in malloc of upgrade!\n");
        return this;
    }

    this->renderer = renderer;
    this->error = true;

    this->upgrade1 = IMG_LoadTexture(this->renderer, "images/upgrade-sign1.png");
    if (!this->upgrade1) {
        fprintf(stderr, "Error creating a texture: %s\n", SDL_GetError());
        return this;
    }

    this->upgrade2 = IMG_LoadTexture(this->renderer, "images/upgrade-sign2.png");
    if (!this->upgrade2) {
        fprintf(stderr, "Error creating a texture: %s\n", SDL_GetError());
        return this;
    }

    this->upgrade3 = IMG_LoadTexture(this->renderer, "images/upgrade-sign3.png");
    if (!this->upgrade3) {
        fprintf(stderr, "Error creating a texture: %s\n", SDL_GetError());
        return this;
    }

    this->upgrade4 = IMG_LoadTexture(this->renderer, "images/upgrade-sign4.png");
    if (!this->upgrade4) {
        fprintf(stderr, "Error creating a texture: %s\n", SDL_GetError());
        return this;
    }

    this->upgrade5 = IMG_LoadTexture(this->renderer, "images/upgrade-sign5.png");
    if (!this->upgrade5) {
        fprintf(stderr, "Error creating a texture: %s\n", SDL_GetError());
        return this;
    }

    if (SDL_QueryTexture(this->upgrade1, NULL, NULL, &this->rect.w, &this->rect.h)) {
        fprintf(stderr, "Error while querying texture: %s\n", SDL_GetError());
        return this;
    }

    this->rect.x = 250;
    this->rect.y = 50;
    this->rect.w *= 5;
    this->rect.h *= 5;

    this->error = false;
    return this;
}

void upgrade_free(struct Upgrade *this) {
    SDL_DestroyTexture(this->upgrade1);
    SDL_DestroyTexture(this->upgrade2);
    SDL_DestroyTexture(this->upgrade3);
    SDL_DestroyTexture(this->upgrade4);
    SDL_DestroyTexture(this->upgrade5);
    free(this);
}

bool upgrade_draw(struct Upgrade *this, Uint8 level) {
    SDL_Texture *image = NULL;
    if (level == 1) {
        image = this->upgrade1;
    } else if (level == 2) {
        image = this->upgrade2;
    } else if (level == 3) {
        image = this->upgrade3;
    } else if (level == 4) {
        image = this->upgrade4;
    } else if (level == 5) {
        image = this->upgrade5;
    }
    
    if (image) {
        if (SDL_RenderCopy(this->renderer, image, NULL, &this->rect)) {
            fprintf(stderr, "Error while rendering texture: %s\n", SDL_GetError());
            return false;
        }
    }

    return true;
}