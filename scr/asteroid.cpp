#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

#include "asteroid.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

std::vector<Asteroid> asteroids;

void AsteroidInit() {
    std::cout << "Asteroid Init" << std::endl;
}

void NewAsteroid(int dis) {
    asteroids.push_back(Asteroid{rand() % dis, -100, 5});
}

void AsteroidMove() {
    for (auto& a : asteroids) {
        a.y += 3;
    }
}

void AsteroidUpdate(int screen_H, int screen_W) {
    asteroids.erase(
        std::remove_if(asteroids.begin(), asteroids.end(), [screen_H](const Asteroid& a) {
                return a.y > screen_H;
            }),
        asteroids.end()
    );
}

void AsteroidReset() {
    asteroids.clear();
}