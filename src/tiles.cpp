#include "tile.h"
#include "position.h"

class LTile : public Tile
{
public:
    LTile()
    {
        tileId = 1;
        cells[0] = {Position(0, 2), Position(1, 0), Position(1, 1), Position(1, 2)};
        cells[1] = {Position(0, 1), Position(1, 1), Position(2, 1), Position(2, 2)};
        cells[2] = {Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 0)};
        cells[3] = {Position(0, 0), Position(0, 1), Position(1, 1), Position(2, 1)};
        Move(0, 3);
    }
};

class JTile : public Tile
{
public:
    JTile()
    {
        tileId = 2;
        cells[0] = {Position(0, 0), Position(1, 0), Position(1, 1), Position(1, 2)};
        cells[1] = {Position(0, 1), Position(0, 2), Position(1, 1), Position(2, 1)};
        cells[2] = {Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 2)};
        cells[3] = {Position(0, 1), Position(1, 1), Position(2, 0), Position(2, 1)};
        Move(0, 3);
    }
};

class ITile : public Tile
{
public:
    ITile()
    {
        tileId = 3;
        cells[0] = {Position(1, 0), Position(1, 1), Position(1, 2), Position(1, 3)};
        cells[1] = {Position(0, 2), Position(1, 2), Position(2, 2), Position(3, 2)};
        cells[2] = {Position(2, 0), Position(2, 1), Position(2, 2), Position(2, 3)};
        cells[3] = {Position(0, 1), Position(1, 1), Position(2, 1), Position(3, 1)};
        Move(-1, 3);
    }
};

class OTile : public Tile
{
public:
    OTile()
    {
        tileId = 4;
        cells[0] = {Position(0, 0), Position(0, 1), Position(1, 0), Position(1, 1)};
        Move(0, 4);
    }
};

class STile : public Tile
{
public:
    STile()
    {
        tileId = 5;
        cells[0] = {Position(0, 1), Position(0, 2), Position(1, 0), Position(1, 1)};
        cells[1] = {Position(0, 1), Position(1, 1), Position(1, 2), Position(2, 2)};
        cells[2] = {Position(1, 1), Position(1, 2), Position(2, 0), Position(2, 1)};
        cells[3] = {Position(0, 0), Position(1, 0), Position(1, 1), Position(2, 1)};
        Move(0, 3);
    }
};

class TTile : public Tile
{
public:
    TTile()
    {
        tileId = 6;
        cells[0] = {Position(0, 1), Position(1, 0), Position(1, 1), Position(1, 2)};
        cells[1] = {Position(0, 1), Position(1, 1), Position(1, 2), Position(2, 1)};
        cells[2] = {Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 1)};
        cells[3] = {Position(0, 1), Position(1, 0), Position(1, 1), Position(2, 1)};
        Move(0, 3);
    }
};

class ZTile : public Tile
{
public:
    ZTile()
    {
        tileId = 7;
        cells[0] = {Position(0, 1), Position(1, 0), Position(1, 1), Position(1, 2)};
        cells[1] = {Position(0, 1), Position(1, 1), Position(1, 2), Position(2, 1)};
        cells[2] = {Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 1)};
        cells[3] = {Position(0, 1), Position(1, 0), Position(1, 1), Position(2, 1)};
        cells[4] = {Position(0, 1), Position(1, 0), Position(1, 1), Position(2, 1)};
        Move(0, 3);
    }
};

class CrossTile : public Tile
{
public:
    CrossTile()
    {
        tileId = 8;
        cells[0] = {Position(0, 1), Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 1)};
        cells[1] = {Position(0, 1), Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 1)};
        cells[2] = {Position(0, 1), Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 1)};
        cells[3] = {Position(0, 1), Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 1)};
        Move(0, 3);
    }
};

class HorseShoeTile : public Tile
{
public:
    HorseShoeTile()
    {
        tileId = 9;
        cells[0] = {Position(0, 0), Position(0, 1), Position(0, 2), Position(1, 0), Position(2, 0), Position(2, 1), Position(2, 2)};
        cells[1] = {Position(0, 0), Position(0, 1), Position(0, 2), Position(1, 0), Position(2, 0), Position(1, 2), Position(2, 2)};
        cells[2] = {Position(0, 0), Position(0, 1), Position(0, 2), Position(1, 2), Position(2, 0), Position(2, 1), Position(2, 2)};
        cells[3] = {Position(0, 0), Position(2, 1), Position(0, 2), Position(1, 0), Position(2, 0), Position(1, 2), Position(2, 2)};
        Move(0, 3);
    }
};