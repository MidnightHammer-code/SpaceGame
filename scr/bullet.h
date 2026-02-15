#ifndef BULLET_H
#define BULLET_H

#include <vector>

struct Bullet
{
    int x;
    int y;
    int type;
    int w = 32;
    int h = 32;

    Bullet(int x_, int y_, int type_)
        : x(x_), y(y_), type(type_) {}
};

void BulletInit();
void BulletAddBullet(int x, int y, int type);
void BulletClearBullet();
void BulletUpdate(int screen_H, int screen_W);
void BulletMove();

extern std::vector<Bullet> bullets;

#endif
