#include "asteroid.h"
#include "bullet.h"
#include "renderer.h"
#include "math.h"
#include "player.h"
#include <SDL2/SDL.h>
#include <vector>

float DIS;
float DIST;

float r1 = 24;
float r2 = 24;

bool CheckCollision(const SDL_Rect& a, const SDL_Rect& b)
{
    return SDL_HasIntersection(&a, &b);
}

bool PlayerColideAsteroidCheck(std::vector<Asteroid> asteroids, SDL_Rect playerCor) {
    for (const auto& b : asteroids) {
    	asteroidCor.x = b.x;
    	asteroidCor.y = b.y;

    	DIS = pythagorasF((b.x - playerCor.x), b.y - playerCor.y);

    	DIST = r1 + r2;

    	if(DIS < DIST){
    		return true;
    	}
    }
    return false;
}

void AsteroidBulletCollide()
{
    for (auto bulletIt = bullets.begin(); bulletIt != bullets.end(); )
    {
        SDL_Rect bulletRect {
            bulletIt->x,
            bulletIt->y,
            bulletIt->w,
            bulletIt->h
        };

        bool bulletRemoved = false;

        for (auto asteroidIt = asteroids.begin(); asteroidIt != asteroids.end(); )
        {
            SDL_Rect asteroidRect {
                asteroidIt->x,
                asteroidIt->y,
                asteroidIt->w,
                asteroidIt->h
            };

            if (CheckCollision(bulletRect, asteroidRect))
            {
                // Remove asteroid
                asteroidIt = asteroids.erase(asteroidIt);

                // Remove bullet
                bulletIt = bullets.erase(bulletIt);
                bulletRemoved = true;
                score += 50;
                break; // bullet is gone, stop checking
            }
            else
            {
                ++asteroidIt;
                //std::cout << "none\n";
            }
        }

        if (!bulletRemoved)
        {
            ++bulletIt;
        }
    }
}


