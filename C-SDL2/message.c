#include "message.h"

struct Message* message_new(SDL_Renderer *renderer, TTF_Font *font, const char *message, bool right) {
    struct Message *this = calloc(1, sizeof(struct Message));
    if (!this) {
        fprintf(stderr, "Error in calloc of score!\n");
        return this;
    }

    this->renderer = renderer;
    this->image = NULL;
    this->font = font;
    this->color = (SDL_Color){255, 255, 255, 255};
    this->rect.x = 5;
    this->rect.y = 5;
    this->message = message;
    this->error = false;
    this->right = right;

    if (!message_update(this, 0)) {
        this->error = true;
    }

    return this;
}

void message_free(struct Message *this) {
    if (this->image) {
        SDL_DestroyTexture(this->image);
    }
    free(this);
}

bool message_update(struct Message *this, Uint32 number) {
    if (this->image)
        SDL_DestroyTexture(this->image);
    
    int length = snprintf(NULL, 0, "%s %d", this->message, number) + 1;
    char message_str[length];
    snprintf(message_str, length, "%s %d", this->message, number);

    SDL_Surface *surface = TTF_RenderText_Blended(this->font, message_str, this->color);
    if (!surface) {
        fprintf(stderr, "Error creating a surface: %s\n", SDL_GetError());
        return false;
    }

    this->image = SDL_CreateTextureFromSurface(this->renderer, surface);
    if (!this->image) {
        fprintf(stderr, "Error creating a texture: %s\n", SDL_GetError());
        return false;
    }

    SDL_FreeSurface(surface);

    // Get a rect from the original image.
    if (SDL_QueryTexture(this->image, NULL, NULL, &this->rect.w, &this->rect.h)) {
        fprintf(stderr, "Error while querying texture: %s\n", SDL_GetError());
        return false;
    }

    if (this->right) {
        this->rect.x = WIDTH - this->rect.w - 8;
    }
    
    return true;
}

bool message_draw(struct Message *this) {
    if (SDL_RenderCopy(this->renderer, this->image, NULL, &this->rect)) {
        fprintf(stderr, "Error while rendering texture: %s\n", SDL_GetError());
        return false;
    }

    return true;
}