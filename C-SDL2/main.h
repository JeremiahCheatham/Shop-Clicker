#ifndef MAIN_H
#define MAIN_H

// Included header files.
#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

// Define directives for constants.
#define MY_SDL_FLAGS (SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_AUDIO)
#define TITLE "Nuofdl Shop Clicker"
#define WIDTH 800
#define HEIGHT 600
#define FPS 60
#define SHOW_FPS false

#endif // MAIN_H