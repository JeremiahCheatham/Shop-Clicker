// Included header files.
#include "game.h"
#include "fps.h"
#include "message.h"
#include "shop.h"
#include "upgrade.h"
#include "scene.h"

struct Game* game_new(SDL_Renderer *renderer) {
    struct Game *this = calloc(1, sizeof(struct Game));
    if (!this) {
        fprintf(stderr, "Error in malloc of game!\n");
        return this;
    }

    this->renderer = renderer;
    this->delta_time = 0;
    this->frame_delay = 1000.0f / FPS;
    this->show_fps = SHOW_FPS;
    this->level = 5;
    this->playing = false;
    this->interval = 0.8;

    // Seed the random number generator with the current time
    srand(time(NULL));

    this->error = true;

    this->splash = IMG_LoadTexture(this->renderer, "images/splashscreen.png");
    if (!this->splash) {
        fprintf(stderr, "Error creating a texture: %s\n", SDL_GetError());
        return false;
    }

    this->music = Mix_LoadMUS( "music/rumble.mp3" );
    if(!this->music) {
        fprintf(stderr, "Failed to load music: %s\n", Mix_GetError());
        return false;
    }

    this->musix = Mix_LoadMUS( "music/jazz.ogg" );
    if(!this->musix) {
        fprintf(stderr, "Failed to load music: %s\n", Mix_GetError());
        return false;
    }
    
    this->font = TTF_OpenFont("fonts/freesansbold.ttf", 35);
    if (!this->font) {
        fprintf(stderr, "Error creating font: %s\n", TTF_GetError());
        return false;
    }

    this->shop = shop_new(renderer);
    if (!this->shop || this->shop->error) {
        return this;
    }

    this->upgrade = upgrade_new(renderer);
    if (!this->upgrade || this->upgrade->error) {
        return this;
    }

    this->scene = scene_new(renderer);
    if (!this->scene || this->scene->error) {
        return this;
    }

    this->stock = message_new(renderer, this->font, "Stock:", false);
    if (!this->stock || this->stock->error) {
        return this;
    }

    this->funds = message_new(renderer, this->font, "Funds:", true);
    if (!this->funds || this->funds->error) {
        return this;
    }

    this->error = false;
    return this;
}

void game_free(struct Game *this) {
    if (this->shop) {
        shop_free(this->shop);
    }

    if (this->upgrade) {
        upgrade_free(this->upgrade);
    }

    if (this->scene) {
        scene_free(this->scene);
    }

    if (this->stock) {
        message_free(this->stock);
    }

    if (this->funds) {
        message_free(this->funds);
    }

    SDL_DestroyTexture(this->splash);

    Mix_FreeMusic(this->music);
    Mix_FreeMusic(this->musix);

    TTF_CloseFont(this->font);

    free(this);
}

void game_mousepressed(struct Game *this, int x, int y) {
    if (y > 220 && y < 600) {
        if (x > 150 && x < 650) {
            this->clicks += this->level;
            message_update(this->stock, this->clicks);
        }
    }else if (y > 50 && y < 100) {
        if (x > 250 && x < 550) {
            if (this->level == 1) {
                if (this->money >= 70) {
                    this->level++;
                    this->money -= 70;
                    message_update(this->funds, this->money);
                }
            } else if (this->level == 2) {
                if (this->money >= 140) {
                    this->level++;
                    this->money -= 140;
                    message_update(this->funds, this->money);
                }
            } else if (this->level == 3) {
                if (this->money >= 210) {
                    this->level++;
                    this->money -= 210;
                    message_update(this->funds, this->money);
                }
            } else if (this->level == 4) {
                if (this->money >= 280) {
                    this->level++;
                    this->money -= 280;
                    message_update(this->funds, this->money);
                }
            } else if (this->level == 5) {
                if (this->money >= 350) {
                    this->level++;
                    this->money -= 350;
                    message_update(this->funds, this->money);
                }
            }
        }
    }
}

bool game_run(struct Game *this) {

    if (rand() % 2) {
        Mix_PlayMusic(this->music, -1);
    } else {
        Mix_PlayMusic(this->musix, -1);
    }

    while (true) {

        // Check key events, key pressed or released.
        while (SDL_PollEvent(&this->event)) {
            switch (this->event.type) {

                case SDL_QUIT:
                    // handling of close button
                    return true;
                case SDL_KEYDOWN:
                    // keyboard API for key pressed
                    switch (this->event.key.keysym.scancode) {
                        case SDL_SCANCODE_ESCAPE:
                            return true;
                        case SDL_SCANCODE_SPACE:
                            this->playing = true;
                            this->level = 1;
                            this->time = 0;
                            this->clicks = 0;
                            this->money = 0;
                            message_update(this->stock, 0);
                            message_update(this->funds, 0);
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (this->playing) {
                        if (this->event.button.button == SDL_BUTTON_LEFT) {
                            game_mousepressed(this, this->event.button.x, this->event.button.y);
                        }
                    }
                    break;
                default:
                    break;
            }
        }

        if (this->playing) {
            this->time += this->delta_time;
            if (this->time >= this->interval && this->clicks >= (this->level * 4)) {
                this->clicks -= (this->level * 4);
                this->money += this->level;
                this->time = 0;
                message_update(this->stock, this->clicks);
                message_update(this->funds, this->money);
            }
        }


        // Clear the existing renderer.
        if (SDL_RenderClear(this->renderer)) {
            fprintf(stderr, "Error while clearing renderer: %s\n", SDL_GetError());
            return false;
        }

        // Draw the scene
        if (!scene_draw(this->scene)) {
            return false;
        }
        
        if (this->playing) {

            // Draw the shop
            if (!shop_draw(this->shop, this->level)) {
                return false;
            }

            // Draw upgrade button
            if (!upgrade_draw(this->upgrade, this->level)) {
                return false;
            }

            // Draw stock
            if (!message_draw(this->stock)) {
                return false;
            }

            // Draw funds
            if (!message_draw(this->funds)) {
                return false;
            }
        } else {
            if (SDL_RenderCopy(this->renderer, this->splash, NULL, NULL)) {
                fprintf(stderr, "Error while rendering texture: %s\n", SDL_GetError());
                return false;
            }
        }

        // Swap the back buffer to the front.
        SDL_RenderPresent(this->renderer);

        // Print FPS to standard output.
        if (this->show_fps)
            fps_print();

        // Calculate delay needed for the FPS.
        this->delta_time = fps_delay(this->frame_delay);
    }
    
    return true;
}