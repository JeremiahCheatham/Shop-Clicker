#include "scene.h"

Scene::Scene(std::shared_ptr<SDL_Renderer> renderer)
    : renderer{renderer},
      backgroundsky{nullptr, SDL_DestroyTexture},
      backgroundhills{nullptr, SDL_DestroyTexture},
      background{nullptr, SDL_DestroyTexture},
      sky_rect{0, 0, 0, 0},
      hills_rect{0, 400, 0, 0},
      ground_rect{0, 500, 0, 0}
{
    this->backgroundsky.reset(IMG_LoadTexture(this->renderer.get(), "images/background.png"));
    if (!this->backgroundsky) {
        auto error = fmt::format("Error creating a texture: {}", SDL_GetError());
        throw std::runtime_error(error);
    }

    if (SDL_QueryTexture(this->backgroundsky.get(), nullptr, nullptr, &this->sky_rect.w, &this->sky_rect.h)) {
        auto error = fmt::format("Error while querying texture: {}", SDL_GetError());
        throw std::runtime_error(error);
    }
    this->sky_rect.w *= 10;
    this->sky_rect.h *= 10;

    this->backgroundhills.reset(IMG_LoadTexture(this->renderer.get(), "images/terrain.png"));
    if (!this->backgroundhills) {
        auto error = fmt::format("Error creating a texture: {}", SDL_GetError());
        throw std::runtime_error(error);
    }

    if (SDL_QueryTexture(this->backgroundhills.get(), nullptr, nullptr, &this->hills_rect.w, &this->hills_rect.h)) {
        auto error = fmt::format("Error while querying texture: {}", SDL_GetError());
        throw std::runtime_error(error);
    }
    this->hills_rect.w *= 10;
    this->hills_rect.h *= 10;

    this->background.reset(IMG_LoadTexture(this->renderer.get(), "images/ground.png"));
    if (!this->background) {
        auto error = fmt::format("Error creating a texture: {}", SDL_GetError());
        throw std::runtime_error(error);
    }

    if (SDL_QueryTexture(this->background.get(), nullptr, nullptr, &this->ground_rect.w, &this->ground_rect.h)) {
        auto error = fmt::format("Error while querying texture: {}", SDL_GetError());
        throw std::runtime_error(error);
    }
    this->ground_rect.w *= 10;
    this->ground_rect.h *= 10;
}

void Scene::draw() {
    if (SDL_RenderCopy(this->renderer.get(), this->backgroundsky.get(), nullptr, &this->sky_rect)) {
        auto error = fmt::format("Error while rendering texture: {}", SDL_GetError());
        throw std::runtime_error(error);
    }

    if (SDL_RenderCopy(this->renderer.get(), this->backgroundhills.get(), nullptr, &this->hills_rect)) {
        auto error = fmt::format("Error while rendering texture: {}", SDL_GetError());
        throw std::runtime_error(error);
    }

    if (SDL_RenderCopy(this->renderer.get(), this->background.get(), nullptr, &this->ground_rect)) {
        auto error = fmt::format("Error while rendering texture: {}", SDL_GetError());
        throw std::runtime_error(error);
    }
}