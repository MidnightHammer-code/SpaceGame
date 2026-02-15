#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>

void MenuInit(int screen_H, int screen_W);
void MenuRenderer(SDL_Renderer *renderer);
void MenuLoop(SDL_Window * window, TTF_Font *font, SDL_Renderer *renderer);
void MenuLoadTTF(TTF_Font *font, SDL_Colour white, SDL_Colour brone);
void MenuPrepare(SDL_Renderer *renderer);
void MenuCleanUp();

extern bool quit;

#endif
