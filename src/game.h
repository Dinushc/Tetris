#pragma once
#include "board.h"
#include "tiles.cpp"
#include "sounds.h"

typedef enum GameDifficulty { EASY, MEDIUM, HARD } GameDifficulty;

class Game
{
public:
    Game(GameDifficulty gameDifficulty);
    ~Game();
    void InitAudio();
    void UnloadAudio();
    void Draw();
    void HandleInput();
    void MoveTile(int key);
    bool gameOver;
    GameDifficulty difficulty;
    int score;
    Music music;

private:
    Tile GetRandomTile();
    std::vector<Tile> GetAllTiles();
    bool IsTileOutside();
    void RotateTile();
    void LockTile();
    bool TileFits();
    void DrawConcrete(int tileLength);
    void Reset();
    void UpdateScore(int linesCleared, int moveDownPoints);
    Board board;
    std::vector<Tile> tiles;
    Tile currentTile;
    Tile nextTile;
    Sound rotateSound;
    Sound clearSound;
};