#include <raylib.h>
#include "game.h"
#include "colors.h"
#include <iostream>
#include <string>
#include <vector>

double lastUpdateTime = 0;
int score = 0;
char scoreText[50];
bool isPaused = false;
char windowTitle[] = "Tetris";
GameDifficulty difficulty = EASY;

typedef enum GameScreen { MENU = 0, GAME, GAMEOVER } GameScreen;

struct Dropdown {
    Rectangle bounds;
    std::vector<std::string> items;
    int selectedIndex;
    bool isOpen;
};

void DrawDropdown(Dropdown& dropdown);
bool EventTriggered(double interval);
void Pause(int screenWidth, int screenHeight);

int main()
{
    const int screenWidth = 500;
    const int screenHeight = 620;

    InitWindow(screenWidth, screenHeight, windowTitle);
    SetTargetFPS(60);

    GameScreen currentScreen = MENU;
    Dropdown dropdown = { { screenWidth / 2 - 100, screenHeight / 2 + 100, 200, 40 }, { "EASY", "MEDIUM", "HARD" }, -1, false };
    Rectangle playButton = { screenWidth / 2 - 50, screenHeight / 2 - 20, 100, 40 };
    Rectangle menuButton = { screenWidth / 2 - 50, screenHeight / 2 - 70, 100, 40 };
    Rectangle quitButton = { screenWidth / 2 - 50, screenHeight / 2 - 120, 100, 40 };

    while (!WindowShouldClose())
    {
        BeginDrawing();

        switch (currentScreen) {
            case MENU:
                ClearBackground(darkGrey);
                if (CheckCollisionPointRec(GetMousePosition(), playButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    currentScreen = GAME;
                }

                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    Vector2 mousePoint = GetMousePosition();
                    if (CheckCollisionPointRec(mousePoint, dropdown.bounds)) {
                        dropdown.isOpen = !dropdown.isOpen;
                    } else if (dropdown.isOpen) {
                        for (int i = 0; i < dropdown.items.size(); i++) {
                            Rectangle itemBounds = { dropdown.bounds.x, dropdown.bounds.y + dropdown.bounds.height * (i + 1), dropdown.bounds.width, dropdown.bounds.height };
                            if (CheckCollisionPointRec(mousePoint, itemBounds)) {
                                dropdown.selectedIndex = i;
                                if (dropdown.items[i] == "EASY") {
                                    difficulty = EASY;
                                } else if (dropdown.items[i] == "MEDIUM") {
                                    difficulty = MEDIUM;
                                } else {
                                    difficulty = HARD;
                                }
                                dropdown.isOpen = false;
                                break;
                            }
                        }
                    } else {
                        dropdown.isOpen = false;
                    }
                }

                DrawText("START MENU", screenWidth / 2 - MeasureText("START MENU", 20) / 2, screenHeight / 2 - 60, 20, RED);
                DrawRectangleRec(playButton, ORANGE);
                DrawText("PLAY", screenWidth / 2 - MeasureText("PLAY", 20) / 2, screenHeight / 2 - 10, 20, DARKGRAY);
                DrawDropdown(dropdown);
                break;

            case GAMEOVER:
                ClearBackground(BLACK);
                if (CheckCollisionPointRec(GetMousePosition(), playButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    currentScreen = GAME;
                }

                if (CheckCollisionPointRec(GetMousePosition(), menuButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    currentScreen = MENU;
                }

                if (CheckCollisionPointRec(GetMousePosition(), quitButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    CloseWindow();
                    return 0;
                }
                sprintf(scoreText, "YOUR SCORE: %d", score);
                DrawText(scoreText, screenWidth / 2 - MeasureText("YOUR SCORE: ", 20) / 2, screenHeight / 2 - 150, 20, GREEN);
                DrawRectangleRec(playButton, DARKBROWN);
                DrawText("RETRY", screenWidth / 2 - MeasureText("RETRY", 20) / 2, screenHeight / 2 - 10, 20, DARKGRAY);
                DrawRectangleRec(menuButton, DARKBROWN);
                DrawText("MENU", screenWidth / 2 - MeasureText("MENU", 20) / 2, screenHeight / 2 - 60, 20, DARKGRAY);
                DrawRectangleRec(quitButton, DARKBROWN);
                DrawText("QUIT", screenWidth / 2 - MeasureText("QUIT", 20) / 2, screenHeight / 2 - 110, 20, DARKGRAY);
                break;

            case GAME:
                Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);
                Game game = Game(difficulty);

                while (!WindowShouldClose() && currentScreen == GAME) {
                    if (IsKeyPressed(KEY_P)) {
                        isPaused = !isPaused;
                    }

                    UpdateMusicStream(game.music);
                    if (!isPaused) {
                        game.HandleInput();
                        if (EventTriggered(0.5)) {
                            game.MoveTile(264);
                        }
                    }

                    BeginDrawing();
                    ClearBackground(GRAY);

                    DrawTextEx(font, "Score", { 365, 15 }, 38, 2, YELLOW);
                    DrawTextEx(font, "Next", { 370, 175 }, 38, 2, YELLOW);

                    if (game.gameOver) {
                        currentScreen = GAMEOVER;
                    }

                    DrawRectangleRounded({ 320, 55, 170, 60 }, 0.1, 6, BLACK);

                    char scoreText[10];
                    sprintf(scoreText, "%d", game.score);
                    score = game.score;
                    Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);
                    DrawTextEx(font, scoreText, { 320 + (170 - textSize.x) / 2, 65 }, 38, 2, WHITE);

                    DrawRectangleRounded({ 320, 215, 170, 180 }, 0.1, 6, BLACK);
                    game.Draw();

                    if (isPaused) {
                        Pause(screenWidth, screenHeight);
                    }

                    EndDrawing();

                    if (WindowShouldClose()) {
                        CloseWindow();
                        return 0;
                    }
                }
                break;
        }

        EndDrawing();
    }

    CloseWindow();
}

void DrawDropdown(Dropdown& dropdown)
{
    DrawRectangleRec(dropdown.bounds, LIGHTGRAY);
    if (dropdown.selectedIndex >= 0) {
        DrawText(dropdown.items[dropdown.selectedIndex].c_str(), dropdown.bounds.x + 10, dropdown.bounds.y + 10, 20, DARKGRAY);
    } else {
        DrawText("DIFFICULTY", dropdown.bounds.x + 10, dropdown.bounds.y + 10, 20, DARKGRAY);
    }

    DrawTriangle(
        { dropdown.bounds.x + dropdown.bounds.width - 20, dropdown.bounds.y + 10 },
        { dropdown.bounds.x + dropdown.bounds.width - 10, dropdown.bounds.y + 10 },
        { dropdown.bounds.x + dropdown.bounds.width - 15, dropdown.bounds.y + 30 },
        DARKGRAY);

    if (dropdown.isOpen) {
        for (int i = 0; i < dropdown.items.size(); i++) {
            Rectangle itemBounds = { dropdown.bounds.x, dropdown.bounds.y + dropdown.bounds.height * (i + 1), dropdown.bounds.width, dropdown.bounds.height };
            DrawRectangleRec(itemBounds, LIGHTGRAY);
            DrawText(dropdown.items[i].c_str(), itemBounds.x + 10, itemBounds.y + 10, 20, DARKGRAY);
        }
    }
}

bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval) {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

void Pause(int screenWidth, int screenHeight)
{
    const char* pauseText = "PAUSE";
    int textWidth = MeasureText(pauseText, 40);
    DrawText(pauseText, (screenWidth - textWidth) / 2, screenHeight / 2 - 20, 40, RED);
}