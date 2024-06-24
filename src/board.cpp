#include "board.h"
#include <iostream>
#include "colors.h"

Board::Board()
{
    numRows = 20;
    numCols = 10;
    cellSize = 30;
    Initialize();
    colors = GetCellColors();
}

void Board::Initialize()
{
    for (int row = 0; row < numRows; row++)
    {
        for (int column = 0; column < numCols; column++)
        {
            board[row][column] = 0;
        }
    }
}

void Board::Print()
{
    for (int row = 0; row < numRows; row++)
    {
        for (int column = 0; column < numCols; column++)
        {
            std::cout << board[row][column] << " ";
        }
        std::cout << std::endl;
    }
}

void Board::Draw()
{
    for (int row = 0; row < numRows; row++)
    {
        for (int column = 0; column < numCols; column++)
        {
            int cellValue = board[row][column];
            DrawRectangle(column * cellSize + 11, row * cellSize + 11, cellSize - 1, cellSize - 1, colors[cellValue]);
        }
    }
}

bool Board::IsCellOutside(int row, int column)
{
    if (row >= 0 && row < numRows && column >= 0 && column < numCols)
    {
        return false;
    }
    return true;
}

bool Board::IsCellEmpty(int row, int column)
{
    if (board[row][column] == 0)
    {
        return true;
    }
    return false;
}

int Board::ClearFullRows()
{
    int completed = 0;
    for (int row = numRows - 1; row >= 0; row--)
    {
        if (IsRowFull(row))
        {
            ClearRow(row);
            completed++;
        }
        else if (completed > 0)
        {
            MoveRowDown(row, completed);
        }
    }
    return completed;
}

bool Board::IsRowFull(int row)
{
    for (int column = 0; column < numCols; column++)
    {
        if (board[row][column] == 0)
        {
            return false;
        }
    }
    return true;
}

void Board::ClearRow(int row)
{
    for (int column = 0; column < numCols; column++)
    {
        board[row][column] = 0;
    }
}

void Board::MoveRowDown(int row, int numRows)
{
    for (int column = 0; column < numCols; column++)
    {
        board[row + numRows][column] = board[row][column];
        board[row][column] = 0;
    }
}
