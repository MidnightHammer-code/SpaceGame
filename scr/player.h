#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>

void PlayerInit(int screen_H, int screen_W);
void PlayerMove(SDL_Event SDL_Event);
void DrawPlayer(SDL_Renderer *renderer, SDL_Texture *playerIMG);
void playerBorderColide(int screen_H, int screen_W);
void playerReset();
bool PlayerRespawn(SDL_Event Event);
void playerUpdate();
void PlayerShootKeyPress(SDL_Event Event);
void PlayerShoots();

extern bool playerMoveLeft;
extern bool playerMoveRight;
extern bool playerMoveUp;
extern bool playerMoveDown;
extern SDL_Rect playerCor;
extern int speed;
extern int score;
extern int difficulty;

#endif
