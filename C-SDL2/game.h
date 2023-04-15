#ifndef GAME_H
#define GAME_H

#include "main.h"

struct Game {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    SDL_Texture *splash;
    Mix_Music *music;
    Mix_Music *musix;
    TTF_Font *font;
    SDL_Rect upgrade_rect;
    float frame_delay;
    float delta_time;
    bool show_fps;
    bool error;
    int clicks;
    int money;
    int level;
    bool playing;
    float interval;
    float time;
    struct Shop *shop;
    struct Upgrade *upgrade;
    struct Scene *scene;
    struct Message *stock;
    struct Message *funds;
};

struct Game* game_new(SDL_Renderer *renderer);
bool game_run(struct Game *this);
void game_free(struct Game *this);

#endif // GAME_H