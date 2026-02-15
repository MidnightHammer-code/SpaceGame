#include "bullet.h"
#include <SDL2/SDL_rect.h>
#include <iostream>
#include <vector>
#include <algorithm>

#include <SDL2/SDL.h>


SDL_Rect bulletTestCor;
SDL_Rect asteroidTestCor;

std::vector<Bullet> bullets;

void BulletInit(){
	std::cout << "bullet init\n";


	bulletTestCor.x = 0;
	bulletTestCor.y = 0;
	bulletTestCor.w = 64;
	bulletTestCor.h = 64;

	asteroidTestCor.x = 0;
	asteroidTestCor.y = 0;
	asteroidTestCor.w = 64;
	asteroidTestCor.h = 64;
}

void BulletAddBullet(int x, int y, int type){
	bullets.push_back(Bullet{x,y,type});
}

void BulletClearBullet(){
	bullets.clear();
}

void BulletUpdate(int screen_H, int screen_W) {
    bullets.erase(
        std::remove_if(bullets.begin(), bullets.end(),
            [screen_H](const Bullet& a) {
                return a.y > screen_H or a.y < -50;
            }),
        bullets.end()
    );
}

void BulletMove() {
    for (auto& a : bullets) {
        a.y -= 10;
    }
}