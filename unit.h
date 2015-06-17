#ifndef UNIT_H
#define UNIT_H

#include "map.h"
#include "rect.h"

class Unit
{
    Map *map;
    unsigned int sprite;
    float speed;
    int currentFrame;
    bool onGround;
    Rect T;
    float x,y;
    float dx,dy;
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
public:
    static const int spriteWidth  = 40;
    static const int spriteHeight = 50;
    static const float frameWidth = 0.142857143;
    static const float frameHeight = 0.25;
    enum sides{Up, Down, Left, Right};
    Unit();
    void update();
    void stop();
    void move(sides);
    void assignMap(Map*);
    void draw();
    void loadSprite(const char*);
    void collision(int);
};

#endif // UNIT_H
