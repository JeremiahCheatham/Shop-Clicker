#include "game.h"

Game::Game()
    : playing{true},
      level{1},
      time{},
      clicks{},
      money{},
      interval{0.8},
      title{"Nuofdl Shop Clicker"},
      window{nullptr, SDL_DestroyWindow},
      renderer{nullptr, SDL_DestroyRenderer},
      splash{nullptr, SDL_DestroyTexture},
      music{nullptr, Mix_FreeMusic},
      musix{nullptr, Mix_FreeMusic},
      scene{nullptr},
      shop{nullptr},
      upgrade{nullptr},
      stock{nullptr},
      funds{nullptr},
      fps{nullptr}
{
    // Initialize SDL2
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        auto error = fmt::format("Error initializing SDL: {}", SDL_GetError());
        throw std::runtime_error(error);
    }

    // Create a window
    this->window = std::shared_ptr<SDL_Window>(SDL_CreateWindow(this->title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->width, this->height, SDL_WINDOW_SHOWN), SDL_DestroyWindow);
    if (!this->window) {
        auto error = fmt::format("Error creating window: {}", SDL_GetError());
        throw std::runtime_error(error);
        SDL_Quit();
    }

    // Create a renderer
    this->renderer.reset(SDL_CreateRenderer(this->window.get(), -1, SDL_RENDERER_ACCELERATED), SDL_DestroyRenderer);
    if (!this->renderer) {
        SDL_Quit();
        auto error = fmt::format("Error creating renderer: {}", SDL_GetError());
        throw std::runtime_error(error);
    }

    // Initialize SDL_ttf
    if(TTF_Init()) {
        SDL_Quit();
        auto error = fmt::format("Error initializing SDL_ttf: {}", TTF_GetError());
        throw std::runtime_error(error);
    }

    // Initialize SDL_image
    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
        TTF_Quit();
        SDL_Quit();
        auto error = fmt::format("Error initializing SDL_image: {}", IMG_GetError());
        throw std::runtime_error(error);
    }

    //Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 1024 ) < 0 ) {
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        auto error = fmt::format("Error initializing SDL_mixer: {}", Mix_GetError());
        throw std::runtime_error(error);
    }

    // Create the stock and funds objects
    this->scene.reset(new Scene(this->renderer));
    this->shop.reset(new Shop(this->renderer));
    this->upgrade.reset(new Upgrade(this->renderer));
    this->stock.reset(new Message(this->renderer, "Stock:", false));
    this->funds.reset(new Message(this->renderer, "Funds:", true));
    this->fps.reset(new Fps(60));
}

void Game::init() {

    this->splash.reset(IMG_LoadTexture(this->renderer.get(), "images/splashscreen.png"));
    if (!this->splash) {
        auto error = fmt::format("Error creating a texture: {}", SDL_GetError());
        throw std::runtime_error(error);
    }

    this->music.reset(Mix_LoadMUS( "music/rumble.mp3" ));
    if(!this->music) {
        auto error = fmt::format("Failed to load music: {}", Mix_GetError());
        throw std::runtime_error(error);
    }

    this->musix.reset(Mix_LoadMUS( "music/jazz.ogg" ));
    if(!this->musix) {
        auto error = fmt::format("Failed to load music: {}", Mix_GetError());
        throw std::runtime_error(error);
    }
}

Game::~Game() {
    // Destroy the unique pointers
    this->scene.reset();
    this->shop.reset();
    this->upgrade.reset();
    this->stock.reset();
    this->funds.reset();

    // Clean up SDL_mixer, SDL_ttf, SDL_image and SDL2.
    Mix_CloseAudio();
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Game::mousepressed(int x, int y) {
    if (y > 220 && y < 600) {
        if (x > 150 && x < 650) {
            this->clicks += this->level;
            this->stock->update(this->clicks);
        }
    }else if (y > 50 && y < 100) {
        if (x > 250 && x < 550) {
            if (this->level == 1) {
                if (this->money >= 70) {
                    this->level++;
                    this->money -= 70;
                    this->funds->update(this->money);
                }
            } else if (this->level == 2) {
                if (this->money >= 140) {
                    this->level++;
                    this->money -= 140;
                    this->funds->update(this->money);
                }
            } else if (this->level == 3) {
                if (this->money >= 210) {
                    this->level++;
                    this->money -= 210;
                    this->funds->update(this->money);
                }
            } else if (this->level == 4) {
                if (this->money >= 280) {
                    this->level++;
                    this->money -= 280;
                    this->funds->update(this->money);
                }
            } else if (this->level == 5) {
                if (this->money >= 350) {
                    this->level++;
                    this->money -= 350;
                    this->funds->update(this->money);
                }
            }
        }
    }
}

void Game::run() {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 1);
    
    //Play the music
    if (dist(gen)) {
        Mix_PlayMusic(this->music.get(), -1);
    } else {
        Mix_PlayMusic(this->musix.get(), -1);
    }

    // Main game loop
    while (true) {
        // Handle events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {

                case SDL_QUIT:
                    // handling of close button
                    return;
                case SDL_KEYDOWN:
                    // keyboard API for key pressed
                    switch (event.key.keysym.scancode) {
                        case SDL_SCANCODE_ESCAPE:
                            return;
                        case SDL_SCANCODE_SPACE:
                            this->playing = true;
                            this->level = 1;
                            this->time = 0;
                            this->clicks = 0;
                            this->money = 0;
                            this->stock->update(0);
                            this->funds->update(0);
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (this->playing) {
                        if (event.button.button == SDL_BUTTON_LEFT) {
                            this->mousepressed(event.button.x, event.button.y);
                        }
                    }
                    break;
                default:
                    break;
            }
        }

        if (this->playing) {
            this->time += this->fps->delta_time();
            if (this->time >= this->interval && this->clicks >= (this->level * 4)) {
                this->clicks -= (this->level * 4);
                this->money += this->level;
                this->time = 0;
                this->stock->update(this->clicks);
                this->funds->update(this->money);
            }
        }

        // Clear the screen
        SDL_RenderClear(this->renderer.get());

        this->scene->draw();

        if (this->playing) {
            this->shop->draw(this->level);
            this->upgrade->draw(this->level);
            this->stock->draw();
            this->funds->draw();
        } else {
            // Draw the images to the renderer.
            if (SDL_RenderCopy(this->renderer.get(), this->splash.get(), nullptr, nullptr)) {
                auto error = fmt::format("Error while rendering texture: {}", SDL_GetError());
                throw std::runtime_error(error);
            }
        }

        // Present the screen
        SDL_RenderPresent(this->renderer.get());

        this->fps->update();
    }
}