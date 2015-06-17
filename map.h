#ifndef MAP_H
#define MAP_H

#include "tile.h"

class Map
{
    Tile M[20][15];
    unsigned int tileSet;
public:
    static const int MapSizeH  = 15;
    static const int MapSizeW  = 20;
    Map();
    Tile::tileType getTileType(int x, int y);
    void setTileType(int x, int y, Tile::tileType type);
    void tmpInitMap();
    void loadMap(const char *);
    void saveMap(const char *);
    void loadTileSet(const char* fileName);
    void draw();
};

#endif // MAP_H
