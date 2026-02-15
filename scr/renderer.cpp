#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <cstddef>
#include <iostream>
#include <vector>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "asteroid.h"
#include "player.h"
#include "bullet.h"

SDL_Texture *playerIMG = NULL;
SDL_Texture *asteroidIMG = NULL;
SDL_Texture *bgIMG = NULL;
SDL_Texture *DiedTexture = NULL;
SDL_Texture *RestartTexture = NULL;
SDL_Texture *ScoreTexture = NULL;
SDL_Texture *ScoreNumbreTexture = NULL;
SDL_Texture *MissileTexture = NULL;

SDL_Rect asteroidCor;
SDL_Rect bgCor;
SDL_Rect DiedCor;
SDL_Rect RestartCor;
SDL_Rect ScoreCor;
SDL_Rect ScoreNumbreCor;
SDL_Rect MissileCor;

SDL_Surface *DiedSurface;
SDL_Surface *RestartSurface;
SDL_Surface *ScoreSurface;
SDL_Surface *ScoreNumbreSurface;

int drawCalls = 0;

void LoadImage(SDL_Renderer *renderer) {
	playerIMG = IMG_LoadTexture(renderer, "assets/images/ship.png");
	bgIMG = IMG_LoadTexture(renderer, "assets/images/space.png");
	asteroidIMG = IMG_LoadTexture(renderer, "assets/images/asteroid.png");
	MissileTexture = IMG_LoadTexture(renderer, "assets/images/missile.png");
}

void RendererInit(int screen_H, int screen_W, SDL_Renderer *renderer) {
	std::cout << "Renderer Init" << std::endl;

	asteroidCor.x = 0;
	asteroidCor.y = 0;
	asteroidCor.w = 64;
	asteroidCor.h = 64;

	bgCor.x = 0;
	bgCor.y = 0;
	bgCor.w = 1024;
	bgCor.h = 1024;

	DiedCor.w = 512;
	DiedCor.h = 128;
	DiedCor.x = (screen_W / 2) - (DiedCor.w / 2);
	DiedCor.y = (screen_H / 2) - (DiedCor.h / 2) - 150;

	RestartCor.w = 256;
	RestartCor.h = 64;
	RestartCor.x = (screen_W / 2) - (RestartCor.w / 2);
	RestartCor.y = (screen_H / 2) - (RestartCor.h / 2);

	ScoreCor.x = 10;
	ScoreCor.y = 10;
	ScoreCor.w = 128;
	ScoreCor.h = 96;

	MissileCor.x = 0;
	MissileCor.y = 0;
	MissileCor.w = 32;
	MissileCor.h = 32;

	LoadImage(renderer);
}


void CleanRendererTextures() {
    if (playerIMG) SDL_DestroyTexture(playerIMG);
    if (bgIMG) SDL_DestroyTexture(bgIMG);
    if (asteroidIMG) SDL_DestroyTexture(asteroidIMG);
    if (DiedTexture) SDL_DestroyTexture(DiedTexture);
    if (RestartTexture) SDL_DestroyTexture(RestartTexture);
    if (ScoreTexture) SDL_DestroyTexture(ScoreTexture);
    if (MissileTexture) SDL_DestroyTexture(MissileTexture);
}

void CleanRendererSurfaces(){
    if (DiedSurface) SDL_FreeSurface(DiedSurface);
    if (RestartSurface) SDL_FreeSurface(RestartSurface);
    if (ScoreSurface) SDL_FreeSurface(ScoreSurface);
}

void TTFLoad(TTF_Font *font, SDL_Colour color, SDL_Renderer *renderer) {

    if (!font) {
        std::cout << TTF_GetError() << std::endl;
    }

    std::string scoreStr = "score: " + std::to_string(score);

	DiedSurface = TTF_RenderText_Solid(font, "PLayer has died", color);
	RestartSurface = TTF_RenderText_Solid(font, "Press R to restart !!!", color);
	ScoreSurface = TTF_RenderText_Solid(font, scoreStr.c_str(), color);
}

void TTFPrepare(SDL_Renderer *renderer) {
	DiedTexture = SDL_CreateTextureFromSurface(renderer, DiedSurface);
	RestartTexture = SDL_CreateTextureFromSurface(renderer, RestartSurface);
	ScoreTexture = SDL_CreateTextureFromSurface(renderer, ScoreSurface);
}

void TTFUpdate(SDL_Renderer *renderer, TTF_Font *font, SDL_Color color) {
    std::string scoreStr = "score: " + std::to_string(score);

    if (ScoreTexture != NULL) {
        SDL_DestroyTexture(ScoreTexture);
    }

    SDL_Surface* newSurface = TTF_RenderText_Solid(font, scoreStr.c_str(), color);
    ScoreTexture = SDL_CreateTextureFromSurface(renderer, newSurface);
    SDL_FreeSurface(newSurface);
}

void TTFRenderSpecial(SDL_Renderer *renderer){
	SDL_RenderCopy(renderer, ScoreTexture, NULL, &ScoreCor);
	drawCalls +=1;
}

void TTFRenderDied(SDL_Renderer *renderer) {
	SDL_RenderCopy(renderer, DiedTexture, NULL, &DiedCor);
	SDL_RenderCopy(renderer, RestartTexture, NULL, &RestartCor);
	drawCalls +=1;
	drawCalls +=1;
}

void RendererDrawBg(SDL_Renderer *renderer) {
	SDL_RenderCopy(renderer, bgIMG, NULL, &bgCor);
	drawCalls +=1;
}

void RenderMissile(SDL_Renderer *renderer, std::vector<Bullet> bullets){
	for(auto a:bullets){
		MissileCor.x = a.x;
		MissileCor.y = a.y;
		SDL_RenderCopy(renderer, MissileTexture, NULL, &MissileCor);
		drawCalls +=1;
	}
}

void RendererDrawAsteroid(const std::vector<Asteroid>& asteroids, SDL_Renderer* renderer) {
    for (const auto& a : asteroids) {
        asteroidCor.x = a.x;
        asteroidCor.y = a.y;
        SDL_RenderCopy(renderer, asteroidIMG, NULL, &asteroidCor);
        drawCalls +=1;
    }
}