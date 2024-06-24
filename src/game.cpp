#include "game.h"
#include <random>

Game::Game(GameDifficulty gameDifficulty)
{
    board = Board();
    difficulty = gameDifficulty;
    tiles = GetAllTiles();
    currentTile = GetRandomTile();
    nextTile = GetRandomTile();
    gameOver = false;
    score = 0;
    InitAudio();
}

Game::~Game()
{
    UnloadAudio();
}

void Game::InitAudio(){
    InitAudioDevice();
    music = LoadMusicStream("sounds/music.wav");
    PlayMusicStream(music);
    rotateSound = LoadSound("sounds/rotate.wav");
    clearSound = LoadSound("sounds/clear.wav"); 
}

void Game::UnloadAudio(){
    UnloadSound(rotateSound);
    UnloadSound(clearSound);
    UnloadMusicStream(music);
    CloseAudioDevice();
}

Tile Game::GetRandomTile()
{
    if (tiles.empty())
    {
        tiles = GetAllTiles();
    }
    int randomIndex = rand() % tiles.size();
    Tile tile = tiles[randomIndex];
    tiles.erase(tiles.begin() + randomIndex);
    return tile;
}

std::vector<Tile> Game::GetAllTiles()
{
    if(difficulty == EASY){
        return {ITile(), JTile(), LTile(), OTile(), STile(), TTile(), ZTile()};
    }
    else if(difficulty == MEDIUM){
        return {ITile(), JTile(), LTile(), OTile(), STile(), TTile(), ZTile(), CrossTile()};
    }
    return {ITile(), JTile(), LTile(), OTile(), STile(), TTile(), ZTile(), CrossTile(), HorseShoeTile()};
}

void Game::Draw()
{
    board.Draw();
    currentTile.Draw(11, 11);
    DrawConcrete(nextTile.tileId);
}

void Game::DrawConcrete(int tileLength)
{
    int length = tileLength == 3 ? 290 : (tileLength == 4 ? 280 : 270);
    nextTile.Draw(255, length);
}

void Game::HandleInput()
{
    int keyPressed = GetKeyPressed();
    if (gameOver && keyPressed != 0)
    {
        gameOver = false;
        Reset();
    }
    if(gameOver){
        return;
    }
    if(keyPressed != 0){
        MoveTile(keyPressed);

        if(keyPressed == KEY_SPACE){
            MoveTile(264);
            MoveTile(264);
            MoveTile(264);
        }
    }
}

void Game::MoveTile(int key)
{
    int first = 0;
    if(key == KEY_DOWN){
        first = 1;
    }
    int second = key == KEY_LEFT ? -1 : key == KEY_RIGHT ? 1 : 0;
    if(key == KEY_UP){
        RotateTile();
        return;
    }
    currentTile.Move(first, second);
    if (IsTileOutside() || !TileFits())
    {
        if(first == 1){
            first *= -1;
            currentTile.Move(first, 0);
            LockTile();
            return;
        }
        currentTile.Move(first, -second);
    }
}

bool Game::IsTileOutside()
{
    std::vector<Position> tiles = currentTile.GetCellPositions();
    for (Position item : tiles)
    {
        if (board.IsCellOutside(item.row, item.column))
        {
            return true;
        }
    }
    return false;
}

void Game::RotateTile()
{
    currentTile.Rotate();
    if (IsTileOutside() || !TileFits())
    {
        currentTile.UndoRotation();
    }
    else
    {
        PlaySound(rotateSound);
    }
}

void Game::LockTile()
{
    std::vector<Position> tiles = currentTile.GetCellPositions();
    for (Position item : tiles)
    {
        board.board[item.row][item.column] = currentTile.tileId;
    }
    currentTile = nextTile;
    if (!TileFits())
    {
        gameOver = true;
        return;
    }
    nextTile = GetRandomTile();
    int rowsCleared = board.ClearFullRows();
    if (rowsCleared > 0)
    {
        PlaySound(clearSound);
        UpdateScore(rowsCleared, 0);
    }
}

bool Game::TileFits()
{
    std::vector<Position> tiles = currentTile.GetCellPositions();
    for (Position item : tiles)
    {
        if (!board.IsCellEmpty(item.row, item.column))
        {
            return false;
        }
    }
    return true;
}

void Game::Reset()
{
    board.Initialize();
    tiles = GetAllTiles();
    currentTile = GetRandomTile();
    nextTile = GetRandomTile();
    score = 0;
}

void Game::UpdateScore(int linesCleared, int moveDownPoints)
{
    int addedScore = linesCleared == 1 ? 100 : (linesCleared == 2 ? 300 : 500);
    score += addedScore;
    score += moveDownPoints;
}
