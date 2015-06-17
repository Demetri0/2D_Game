#include "map.h"
#include "LoadTGA.h"

Map::Map()
{
    for (int i = 0; i < Map::MapSizeW; ++i) {
        for (int j = 0; j < Map::MapSizeH; ++j) {
            M[i][j].setType(Tile::Warp);
        }
    }
}

void Map::tmpInitMap(){
    int n = 14;
    for (int i = 0; i < Map::MapSizeW; ++i) {
        M[i][n].setType(Tile::Wall);
    }
    M[0][n-1].setType(Tile::Wall);
    n = 12;
    for (int i = 8; i < 18; ++i) {
        M[i][n].setType(Tile::Wall);
    }
    n = 9;
    for (int i = 2; i < 12; ++i) {
        M[i][n].setType(Tile::Wall);
    }
    n = 10;
    for (int i = 2; i < 12; ++i) {
        M[i][n].setType(Tile::Bonus);
    }
    n = 6;
    for (int i = 14; i < 20; ++i) {
        M[i][n].setType(Tile::Wall);
    }
    n = 3;
    for (int i = 8; i < 14; ++i) {
        M[i][n].setType(Tile::Wall);
    }
    M[3][n].setType(Tile::Bonus);
}

Tile::tileType Map::getTileType(int x, int y){
    if(x >= MapSizeW || y >= MapSizeH || x < 0 || y < 0) return Tile::Wall;
    return M[x][y].getType();
}

void Map::setTileType(int x, int y, Tile::tileType type){
    if(x >= MapSizeW || y >= MapSizeH || x < 0 || y < 0) return;
    M[x][y].setType(type);
}
/*
void Map::loadMap(const char *fileName){

}
void Map::saveMap(const char *fileName){

}
*/
void Map::draw(){
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tileSet);
    for (int i = 0; i < Map::MapSizeW; ++i) {
        for (int j = 0; j < Map::MapSizeH; ++j) {
            M[i][j].draw(i,j);
        }
    }
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);
}


void Map::loadTileSet(const char *fileName)
{
    tileSet = LoadTGATexture(fileName);
}
