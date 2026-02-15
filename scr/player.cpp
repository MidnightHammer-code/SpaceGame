#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "bullet.h"

int speed = 4;

int score = 0;

int difficulty = 250;

SDL_Rect playerCor;

bool playerMoveLeft = false;
bool playerMoveRight = false;
bool playerMoveUp = false;
bool playerMoveDown = false;

bool playerShoot = false;

void PlayerInit(int screen_H, int screen_W) {
	std::cout << "player Init" << std::endl;

    playerCor.w = 64;
    playerCor.h = 64;
	playerCor.x = (screen_W / 2) - (playerCor.w / 2);
	playerCor.y = (screen_H / 2) - (playerCor.h / 2);
}

void PlayerMove(SDL_Event Event) {
    if (Event.type == SDL_KEYDOWN) {

      	if (Event.key.keysym.sym == SDLK_w) {
            playerMoveUp = true;
        }

        if (Event.key.keysym.sym == SDLK_s) {
            playerMoveDown = true;
        }

        if (Event.key.keysym.sym == SDLK_d) {
            playerMoveRight = true;
        }

        if (Event.key.keysym.sym == SDLK_a) {
            playerMoveLeft = true;
        }

        if (Event.key.keysym.sym == SDLK_UP) {
            playerMoveUp = true;
        }

        if (Event.key.keysym.sym == SDLK_DOWN) {
            playerMoveDown = true;
        }

        if (Event.key.keysym.sym == SDLK_RIGHT) {
            playerMoveRight = true;
        }

        if (Event.key.keysym.sym == SDLK_LEFT) {
            playerMoveLeft = true;
        }
    }

    if (Event.type == SDL_KEYUP) {
	   if (Event.key.keysym.sym == SDLK_w) {
            playerMoveUp = false;
        }

        if (Event.key.keysym.sym == SDLK_s) {
            playerMoveDown = false;
        }

        if (Event.key.keysym.sym == SDLK_d) {
            playerMoveRight = false;
        }

        if (Event.key.keysym.sym == SDLK_a) {
            playerMoveLeft = false;
        }

        if (Event.key.keysym.sym == SDLK_UP) {
            playerMoveUp = false;
        }

        if (Event.key.keysym.sym == SDLK_DOWN) {
            playerMoveDown = false;
        }

        if (Event.key.keysym.sym == SDLK_RIGHT) {
            playerMoveRight = false;
        }

        if (Event.key.keysym.sym == SDLK_LEFT) {
            playerMoveLeft = false;
        }
    }
}


void PlayerShootKeyPress(SDL_Event Event){
    if (Event.type == SDL_KEYDOWN) {
        if (Event.key.keysym.sym == SDLK_SPACE) {
            playerShoot = true;
        }
    }

    if (Event.type == SDL_KEYUP) {
        if (Event.key.keysym.sym == SDLK_SPACE) {
            playerShoot = false;
        }
    }
}

void PlayerShoots(){
    if(playerShoot){
        BulletAddBullet(playerCor.x, playerCor.y, 0);
    }
}

bool PlayerRespawn(SDL_Event Event) {
    if (Event.type == SDL_KEYDOWN) {
        if (Event.key.keysym.sym == SDLK_r) {
            score = 0;
            return true;
        }
    }

    return false;
}

void DrawPlayer(SDL_Renderer *renderer, SDL_Texture *playerIMG) {
	SDL_RenderCopy(renderer, playerIMG, NULL, &playerCor);
}

void playerBorderColide(int screen_H, int screen_W) {

	if(playerCor.x < 0) {
		playerMoveLeft = false;
	}
	if(playerCor.y < 0) {
		playerMoveUp = false;
	}
	if(playerCor.y > (screen_H - playerCor.h)) {
		playerMoveDown = false;
	}
	if(playerCor.x > (screen_W - playerCor.w)) {
		playerMoveRight = false;
	}

}

void playerUpdate(){
    score += 10;

    if(difficulty > 100) {
        difficulty -= 1;
    }
}

void playerReset() {
    playerMoveLeft = false;
    playerMoveRight = false;
    playerMoveUp = false;
    playerMoveDown = false;

    score = 0;
}