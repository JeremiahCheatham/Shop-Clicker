#include "upgrade.h"

Upgrade::Upgrade(std::shared_ptr<SDL_Renderer> renderer)
    : renderer{renderer},
      upgrade1{nullptr, SDL_DestroyTexture},
      upgrade2{nullptr, SDL_DestroyTexture},
      upgrade3{nullptr, SDL_DestroyTexture},
      upgrade4{nullptr, SDL_DestroyTexture},
      upgrade5{nullptr, SDL_DestroyTexture},
      rect{250, 50, 0, 0}
{
    this->upgrade1.reset(IMG_LoadTexture(this->renderer.get(), "images/upgrade-sign1.png"));
    if (!this->upgrade1) {
        auto error = fmt::format("Error creating a texture: {}", SDL_GetError());
        throw std::runtime_error(error);
    }

    this->upgrade2.reset(IMG_LoadTexture(this->renderer.get(), "images/upgrade-sign2.png"));
    if (!this->upgrade2) {
        auto error = fmt::format("Error creating a texture: {}", SDL_GetError());
        throw std::runtime_error(error);
    }

    this->upgrade3.reset(IMG_LoadTexture(this->renderer.get(), "images/upgrade-sign3.png"));
    if (!this->upgrade3) {
        auto error = fmt::format("Error creating a texture: {}", SDL_GetError());
        throw std::runtime_error(error);
    }

    this->upgrade4.reset(IMG_LoadTexture(this->renderer.get(), "images/upgrade-sign4.png"));
    if (!this->upgrade4) {
        auto error = fmt::format("Error creating a texture: {}", SDL_GetError());
        throw std::runtime_error(error);
    }

    this->upgrade5.reset(IMG_LoadTexture(this->renderer.get(), "images/upgrade-sign5.png"));
    if (!this->upgrade5) {
        auto error = fmt::format("Error creating a texture: {}", SDL_GetError());
        throw std::runtime_error(error);
    }

    if (SDL_QueryTexture(this->upgrade1.get(), nullptr, nullptr, &this->rect.w, &this->rect.h)) {
        auto error = fmt::format("Error while querying texture: {}", SDL_GetError());
        throw std::runtime_error(error);
    }
    this->rect.w *= 5;
    this->rect.h *= 5;
}

void Upgrade::draw(unsigned int upgrade) {
    SDL_Texture *image{};

    if (upgrade == 1) {
        image = this->upgrade1.get();
    } else if (upgrade == 2) {
        image = this->upgrade2.get();
    } else if (upgrade == 3) {
        image = this->upgrade3.get();
    } else if (upgrade == 4) {
        image = this->upgrade4.get();
    } else if (upgrade == 5) {
        image = this->upgrade5.get();
    }
    
    if (image) {
        if (SDL_RenderCopy(this->renderer.get(), image, nullptr, &this->rect)) {
            auto error = fmt::format("Error while rendering texture: {}", SDL_GetError());
            throw std::runtime_error(error);
        }
    }
}