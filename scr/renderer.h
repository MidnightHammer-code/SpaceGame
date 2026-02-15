#ifndef RENDERER_H
#define RENDERER_H

#include "asteroid.h"
#include "bullet.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <vector>

void LoadImage(SDL_Renderer *renderer);
void CleanRendererTextures();
void CleanRendererSurfaces();
void RendererInit(int screen_H, int screen_W, SDL_Renderer *renderer);
void RendererDrawBg(SDL_Renderer *renderer);
void RendererDrawAsteroid(const std::vector<Asteroid>& asteroids, SDL_Renderer* renderer);
void TTFLoad(TTF_Font *font, SDL_Colour color, SDL_Renderer *renderer);
void TTFPrepare(SDL_Renderer *renderer);
void TTFRenderDied(SDL_Renderer *renderer);
void TTFUpdate(SDL_Renderer *renderer, TTF_Font *font, SDL_Colour color);
void TTFRenderSpecial(SDL_Renderer *renderer);
void RenderMissile(SDL_Renderer *renderer, std::vector<Bullet> bullets);

extern SDL_Texture *playerIMG;

extern SDL_Rect asteroidCor;
extern SDL_Rect bgCor;
extern SDL_Rect DiedCor;
extern SDL_Rect RestartCor;
extern SDL_Rect ScoreCor;
extern SDL_Rect ScoreNumbreCor;
extern SDL_Rect MissileCor;

extern int drawCalls;

#endif
