#ifndef GAME_H
#define GAME_H

#include "main.h"
#include "scene.h"
#include "shop.h"
#include "upgrade.h"
#include "message.h"
#include "fps.h"

class Game {
public:
    Game();
    ~Game();

    void init();
    void run();
    void mousepressed(int x, int y);

    static constexpr int width = 800;
    static constexpr int height = 600;
    bool playing;
    int level;
    float time;
    int clicks;
    int money;
    float interval;

private:
    const std::string title;
    std::shared_ptr<SDL_Window> window;
    std::shared_ptr<SDL_Renderer> renderer;
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> splash;
    std::unique_ptr<Mix_Music, decltype(&Mix_FreeMusic)> music;
    std::unique_ptr<Mix_Music, decltype(&Mix_FreeMusic)> musix;
    std::unique_ptr<Scene> scene;
    std::unique_ptr<Shop> shop;
    std::unique_ptr<Upgrade> upgrade;
    std::unique_ptr<Message> stock;
    std::unique_ptr<Message> funds;
    std::unique_ptr<Fps> fps;
};

#endif // GAME_H