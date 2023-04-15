// Included header files.
#include "shop.h"

struct Shop* shop_new(SDL_Renderer *renderer) {
    struct Shop *this = calloc(1, sizeof(struct Shop));
    if (!this) {
        fprintf(stderr, "Error in malloc of shop!\n");
        return this;
    }

    this->renderer = renderer;
    this->error = true;

    this->level1 = IMG_LoadTexture(this->renderer, "images/level1.png");
    if (!this->level1) {
        fprintf(stderr, "Error creating a texture: %s\n", SDL_GetError());
        return this;
    }

    this->level2 = IMG_LoadTexture(this->renderer, "images/level2.png");
    if (!this->level2) {
        fprintf(stderr, "Error creating a texture: %s\n", SDL_GetError());
        return this;
    }

    this->level3 = IMG_LoadTexture(this->renderer, "images/level3.png");
    if (!this->level3) {
        fprintf(stderr, "Error creating a texture: %s\n", SDL_GetError());
        return this;
    }

    this->level4 = IMG_LoadTexture(this->renderer, "images/level4.png");
    if (!this->level4) {
        fprintf(stderr, "Error creating a texture: %s\n", SDL_GetError());
        return this;
    }

    this->level5 = IMG_LoadTexture(this->renderer, "images/level5.png");
    if (!this->level5) {
        fprintf(stderr, "Error creating a texture: %s\n", SDL_GetError());
        return this;
    }

    this->level6 = IMG_LoadTexture(this->renderer, "images/level6.png");
    if (!this->level6) {
        fprintf(stderr, "Error creating a texture: %s\n", SDL_GetError());
        return this;
    }

    if (SDL_QueryTexture(this->level1, NULL, NULL, &this->rect.w, &this->rect.h)) {
        fprintf(stderr, "Error while querying texture: %s\n", SDL_GetError());
        return false;
    }

    this->rect.x = 150;
    this->rect.y = 220;
    this->rect.w *= 10;
    this->rect.h *= 10;

    this->error = false;
    return this;
}

void shop_free(struct Shop *this) {
    SDL_DestroyTexture(this->level1);
    SDL_DestroyTexture(this->level2);
    SDL_DestroyTexture(this->level3);
    SDL_DestroyTexture(this->level4);
    SDL_DestroyTexture(this->level5);
    SDL_DestroyTexture(this->level6);
    free(this);
}

bool shop_draw(struct Shop *this, Uint8 level) {
    SDL_Texture *image = NULL;
    if (level == 1) {
        image = this->level1;
    } else if (level == 2) {
        image = this->level2;
    } else if (level == 3) {
        image = this->level3;
    } else if (level == 4) {
        image = this->level4;
    } else if (level == 5) {
        image = this->level5;
    } else if (level == 6) {
        image = this->level6;
    }
    
    if (SDL_RenderCopy(this->renderer, image, NULL, &this->rect)) {
        fprintf(stderr, "Error while rendering texture: %s\n", SDL_GetError());
        return false;
    }

    return true;
}