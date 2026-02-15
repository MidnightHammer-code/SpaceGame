#ifndef ASTEROID_H
#define ASTEROID_H

#include <vector>

struct Asteroid
{
    int x;
    int y;
    int speed;
    int w = 64;
    int h = 64;

    Asteroid(int x_, int y_, int speed_)
        : x(x_), y(y_), speed(speed_) {}
};

extern std::vector<Asteroid> asteroids;

void AsteroidInit();
void NewAsteroid(int dis);
void AsteroidMove();
void AsteroidUpdate(int screen_H, int screen_W);
void AsteroidReset();

#endif
