#ifndef SCENE_H
#define SCENE_H

#include "main.h"

class Scene {
public:
    Scene(std::shared_ptr<SDL_Renderer> renderer);

    void draw();

private:
    std::shared_ptr<SDL_Renderer> renderer;
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> backgroundsky;
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> backgroundhills;
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> background;
    SDL_Rect sky_rect;
    SDL_Rect hills_rect;
    SDL_Rect ground_rect;
};

#endif // SCENE_H