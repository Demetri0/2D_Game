#include "unit.h"
#include "rect.h"
#include <GL/glut.h>
#include <iostream>
GLuint LoadTGATexture(const char*);
Unit::Unit()
{
    x = 50;
    y = 398;
    dy = 0;
    T.x1 = 0.0;
    T.x2 = 0.142857143;
    T.y1 = 0.0;
    T.y2 = 0.25;
    currentFrame = 0;
    onGround = true;
    speed = 10.0;
}

void Unit::moveUp()
{
    if(onGround){
        onGround = false;
        dy = 50;
    }
}

void Unit::moveDown()
{
//    y += dy;
}

void Unit::moveLeft()
{
//    dx = -0.1;
    dx = -1.5;
}

void Unit::moveRight()
{
//    dx = 0.1;
    dx = 1.5;
}

void Unit::stop(){
    currentFrame = 0;
    if(!onGround){
        if(dx < 0){
            T.y1 = 0.75;
            T.y2 = 1.0;
        }else if(dx > 0){
            T.y1 = 0.5;
            T.y2 = 0.75;
        }
    }else{
        T.y1 = 0.0;
        T.y2 = 0.25;
    }
    dx = 0;
}

void Unit::move(sides side){
    switch (side) {
    case Up:
                moveUp();
                break;
    case Down:
                moveDown();
                break;
    case Left:
                moveLeft();
                break;
    case Right:
                moveRight();
                break;
    }
}

void Unit::collision(int dir){
    for (int i = x/Tile::tileSize; i < (x+spriteWidth)/Tile::tileSize; ++i) {
        for (int j = y/Tile::tileSize; j < (y+spriteHeight)/Tile::tileSize; ++j) {
            if( map->getTileType(i,j) == Tile::Wall ){
                if((dir == 1) && dx > 0){
                    x = i*Tile::tileSize - spriteWidth;
                }else if((dir == 1) && dx < 0){
                    x = i*Tile::tileSize + Tile::tileSize;
                }
                if((dir == 0) && dy < 0){
                    y = j*Tile::tileSize - spriteHeight;
                    onGround = true;
                    dy = 0;
                }else if((dir == 0) && dy > 0){
                    y = j*Tile::tileSize + Tile::tileSize;
                    dy = dy/2;
                }
                return;
            }
            if( map->getTileType(i,j) == Tile::Bonus ){
                map->setTileType(i,j,Tile::Warp);
            }
        }
    }
}

void Unit::update(){
    y += speed-dy;
    dy-= speed;
    collision(0);
    x += dx * speed;
    collision(1);
    //Animation begin
    T.x1 = frameWidth * currentFrame;
    T.x2 = T.x1 + frameWidth;
    if(dx > 0){
        T.y1 = 0;
        T.y2 = 0.25;
    }else if(dx < 0){
        T.y1 = 0.25;
        T.y2 = 0.5;
    }
    if(currentFrame == 6) currentFrame = 0;
    currentFrame++;
}

void Unit::assignMap(Map* _map){
    map = _map;
}

void Unit::loadSprite(const char *fileName){
    sprite = LoadTGATexture(fileName);
}

void Unit::draw(){
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, sprite);

    glBegin(GL_QUADS);
        glColor3ub(255,255,255);

        glTexCoord2f(T.x1, T.y1);
        glVertex3f(x                  , y                    , 1);

        glTexCoord2f(T.x2, T.y1);
        glVertex3f(x+Unit::spriteWidth, y                    , 1);

        glTexCoord2f(T.x2, T.y2);
        glVertex3f(x+Unit::spriteWidth, y+Unit::spriteHeight , 1);

        glTexCoord2f(T.x1, T.y2);
        glVertex3f(x                  , y+Unit::spriteHeight, 1);
    glEnd();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);
}
