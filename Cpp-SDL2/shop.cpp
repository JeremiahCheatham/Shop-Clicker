#include "shop.h"

Shop::Shop(std::shared_ptr<SDL_Renderer> renderer)
    : renderer{renderer},
      level1{nullptr, SDL_DestroyTexture},
      level2{nullptr, SDL_DestroyTexture},
      level3{nullptr, SDL_DestroyTexture},
      level4{nullptr, SDL_DestroyTexture},
      level5{nullptr, SDL_DestroyTexture},
      level6{nullptr, SDL_DestroyTexture},
      rect{150, 220, 0, 0}
{
    this->level1.reset(IMG_LoadTexture(this->renderer.get(), "images/level1.png"));
    if (!this->level1) {
        auto error = fmt::format("Error creating a texture: {}", SDL_GetError());
        throw std::runtime_error(error);
    }

    this->level2.reset(IMG_LoadTexture(this->renderer.get(), "images/level2.png"));
    if (!this->level2) {
        auto error = fmt::format("Error creating a texture: {}", SDL_GetError());
        throw std::runtime_error(error);
    }

    this->level3.reset(IMG_LoadTexture(this->renderer.get(), "images/level3.png"));
    if (!this->level3) {
        auto error = fmt::format("Error creating a texture: {}", SDL_GetError());
        throw std::runtime_error(error);
    }

    this->level4.reset(IMG_LoadTexture(this->renderer.get(), "images/level4.png"));
    if (!this->level4) {
        auto error = fmt::format("Error creating a texture: {}", SDL_GetError());
        throw std::runtime_error(error);
    }

    this->level5.reset(IMG_LoadTexture(this->renderer.get(), "images/level5.png"));
    if (!this->level5) {
        auto error = fmt::format("Error creating a texture: {}", SDL_GetError());
        throw std::runtime_error(error);
    }

    this->level6.reset(IMG_LoadTexture(this->renderer.get(), "images/level6.png"));
    if (!this->level6) {
        auto error = fmt::format("Error creating a texture: {}", SDL_GetError());
        throw std::runtime_error(error);
    }

    if (SDL_QueryTexture(this->level1.get(), nullptr, nullptr, &this->rect.w, &this->rect.h)) {
        auto error = fmt::format("Error while querying texture: {}", SDL_GetError());
        throw std::runtime_error(error);
    }
    this->rect.w *= 10;
    this->rect.h *= 10;
}

void Shop::draw(unsigned int level) {
    SDL_Texture *image{};

    if (level == 1) {
        image = this->level1.get();
    } else if (level == 2) {
        image = this->level2.get();
    } else if (level == 3) {
        image = this->level3.get();
    } else if (level == 4) {
        image = this->level4.get();
    } else if (level == 5) {
        image = this->level5.get();
    } else if (level == 6) {
        image = this->level6.get();
    }
    
    if (image) {
        if (SDL_RenderCopy(this->renderer.get(), image, nullptr, &this->rect)) {
            auto error = fmt::format("Error while rendering texture: {}", SDL_GetError());
            throw std::runtime_error(error);
        }
    }
}