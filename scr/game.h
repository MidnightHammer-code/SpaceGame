#ifndef GAME_H
#define GAME_H

#include "asteroid.h"
#include <SDL2/SDL_rect.h>

bool PlayerColideAsteroidCheck(std::vector<Asteroid> asteroids, SDL_Rect playerCor);
void AsteroidBulletCollide();

#endif
