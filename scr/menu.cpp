#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <cstddef>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

bool menuRun = true;
bool quit = false;

SDL_Surface *GameNameSurface;
SDL_Surface *StartGameSurface;

SDL_Texture *GameNameTexture;
SDL_Texture *StartGameTexture;

SDL_Rect GameNameCor;
SDL_Rect StartGameCor;
SDL_Rect MouseCor;

void MenuInit(int screen_H, int screen_W) {
	std::cout << "Menu Init\n";
    GameNameCor.w = 200;
    GameNameCor.h = 100;
    GameNameCor.x = screen_W - (screen_W / 10 * 9);
    GameNameCor.y = screen_H - (screen_H / 20 * 19);

    StartGameCor.w = 200;
    StartGameCor.h = 50;
    StartGameCor.x = screen_W - (screen_W / 9 * 8);
    StartGameCor.y = 200;

    MouseCor.w = 32;
    MouseCor.h = 32;
    MouseCor.x = 0;
    MouseCor.y = 0;
}

void MenuRenderer(SDL_Renderer *renderer) {
    SDL_RenderCopy(renderer, GameNameTexture, NULL, &GameNameCor);
    SDL_RenderCopy(renderer, StartGameTexture, NULL, &StartGameCor);
}

void MenuLoadTTF(TTF_Font *font, SDL_Colour colour2, SDL_Colour colour3) {
    if (!font) {
        std::cout << TTF_GetError() << std::endl;
    }

    GameNameSurface = TTF_RenderText_Solid(font, "Space Game", colour2);
    StartGameSurface = TTF_RenderText_Solid(font, "Play        ", colour3);
}

void MenuPrepare(SDL_Renderer *renderer){
    GameNameTexture = SDL_CreateTextureFromSurface(renderer, GameNameSurface);
    StartGameTexture = SDL_CreateTextureFromSurface(renderer, StartGameSurface);
}

void MenuCleanUp() {
    SDL_DestroyTexture(GameNameTexture);
    SDL_DestroyTexture(StartGameTexture);

    SDL_FreeSurface(GameNameSurface);
    SDL_FreeSurface(StartGameSurface);
}

void MenuColision(SDL_Event Event) {

    if (SDL_HasIntersection(&MouseCor, &StartGameCor)) {
        if (Event.type == SDL_MOUSEBUTTONDOWN) {
            if (Event.button.button == SDL_BUTTON_LEFT) {
                menuRun = false;
            }
        }
    }
}

void MenuLoop(SDL_Window * window, TTF_Font *font, SDL_Renderer *renderer) {

	Uint32 time = SDL_GetTicks();

	Uint32 startMenuTime = SDL_GetTicks();
    float MenuFrameCount = 0;
    
    int MenuFps = 60;
	int desiredDelta = 1000 / MenuFps;


	while (menuRun) {
		int startMenuLoop = SDL_GetTicks();

        MenuFrameCount++;
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - startMenuTime >= 1000) { // Every second
            MenuFps = MenuFrameCount;
            MenuFrameCount = 0;
            startMenuTime = currentTime;
            std::cout << "FPS: " << MenuFps << std::endl;
        }

        SDL_GetMouseState(&MouseCor.x, &MouseCor.y);

        MenuRenderer(renderer);


        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);

		SDL_Event Event;
        while (SDL_PollEvent(&Event)){

            if (Event.type == SDL_QUIT) {
                quit = true;
                menuRun = false;
            }

            MenuColision(Event);
        }
        int delta = SDL_GetTicks() - startMenuLoop;
		if (delta < desiredDelta) {
			SDL_Delay(desiredDelta - delta);
		}
	}
}