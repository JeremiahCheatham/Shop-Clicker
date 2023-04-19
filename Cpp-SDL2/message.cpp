#include "message.h"

Message::Message(std::shared_ptr<SDL_Renderer> renderer, std::string message, bool right)
    : renderer{renderer},
      image{nullptr, SDL_DestroyTexture},
      font{nullptr, TTF_CloseFont},
      rect{5, 5, 0, 0},
      color{255, 255, 255, 255},
      message{message},
      right{right}
{
    this->font.reset(TTF_OpenFont("fonts/freesansbold.ttf", 35));
    if (!this->font) {
        auto error = fmt::format("Error creating font: {}", TTF_GetError());
        throw std::runtime_error(error);
    }

    this->update(0);
}

void Message::update(int num) {
    std::string score_text{this->message + std::to_string(num)};

    std::shared_ptr<SDL_Surface> surface{TTF_RenderText_Blended(this->font.get(), score_text.c_str(), this->color)};
    if (!surface) {
        auto error = fmt::format("Error creating a surface: {}", SDL_GetError());
        throw std::runtime_error(error);
    }

    this->image.reset(SDL_CreateTextureFromSurface(this->renderer.get(), surface.get()));
    if (!this->image) {
        auto error = fmt::format("Error creating a texture: {}", SDL_GetError());
        throw std::runtime_error(error);
    }

    // Get a rect from the image.
    if (SDL_QueryTexture(this->image.get(), nullptr, nullptr, &this->rect.w, &this->rect.h)) {
        auto error = fmt::format("Error while querying texture: {}", SDL_GetError());
        throw std::runtime_error(error);
    }

    if (this->right) {
        this->rect.x = 800   - this->rect.w - 8;
    }
}

void Message::draw() {
    if (SDL_RenderCopy(this->renderer.get(), this->image.get(), nullptr, &this->rect)) {
        auto error = fmt::format("Error while rendering texture: {}", SDL_GetError());
        throw std::runtime_error(error);
    }
}