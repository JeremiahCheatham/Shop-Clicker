#ifndef MESSAGE_H
#define MESSAGE_H

#include "main.h"

class Message {
public:
    Message(std::shared_ptr<SDL_Renderer> renderer, std::string message, bool right);

    void update(int num);
    void draw();

private:
    std::shared_ptr<SDL_Renderer> renderer;
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> image;
    std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> font;
    SDL_Rect rect;
    SDL_Color color;
    std::string message;
    bool right;
};

#endif // MESSAGE_H