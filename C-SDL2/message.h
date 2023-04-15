#ifndef MESSAGE_H
#define MESSAGE_H

#include "main.h"

struct Message {
    SDL_Renderer *renderer;
    SDL_Texture* image;
    TTF_Font *font;
    SDL_Color color;
    SDL_Rect rect;
    const char *message;
    bool error;
    bool right;
};

struct Message* message_new(SDL_Renderer *renderer, TTF_Font *font, const char *message, bool left);
void message_free(struct Message *this);
bool message_update(struct Message *this, Uint32 number);
bool message_draw(struct Message *this);

#endif