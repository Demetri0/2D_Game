#include "tile.h"
#include "rect.h"
#include <GL/glut.h>
#include <iostream>

Tile::Tile()
{
    type = Warp;
}

void Tile::setType(tileType _type){
    type = _type;
}
Tile::tileType Tile::getType(){
    return type;
}

void Tile::draw(int x, int y){

    Rect T;
    switch (type) {

        case Wall:
                    T.x1 = 0.0;
                    T.x2 = 0.5;
                    T.y1 = 0.0;
                    T.y2 = 0.5;
                    break;
        case Warp:
                    T.x1 = 0.5;
                    T.x2 = 1.0;
                    T.y1 = 0.5;
                    T.y2 = 1.0;
                    break;
        case Bonus:
                    T.x1 = 0.5;
                    T.x2 = 1.0;
                    T.y1 = 0.0;
                    T.y2 = 0.5;
                    break;
        default:
                    T.x1 = 0.0;
                    T.x2 = 0.5;
                    T.y1 = 0.0;
                    T.y2 = 0.5;
    }
    glBegin(GL_QUADS);
        glColor3ub(255,255,255);

        glTexCoord2f(T.x1               , T.y1);
        glVertex3f(x*tileSize           , y*tileSize            , 0);

        glTexCoord2f(T.x1               , T.y2);
        glVertex3f(x*tileSize+tileSize  , y*tileSize            , 0);

        glTexCoord2f(T.x2               , T.y2);
        glVertex3f(x*tileSize+tileSize  , y*tileSize+tileSize   , 0);

        glTexCoord2f(T.x2               , T.y1);
        glVertex3f(x*tileSize           , y*tileSize+tileSize   , 0);

    glEnd();

}
