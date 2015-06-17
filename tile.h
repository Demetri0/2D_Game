#ifndef TILE_H
#define TILE_H

class Tile
{
public:
    enum tileType{Warp, Wall, Bonus};
    static const int tileSize = 32;
    Tile();
    void setType(tileType _type);
    tileType getType();
    void draw(int,int);
  private:
    tileType type;
};

#endif // TILE_H
