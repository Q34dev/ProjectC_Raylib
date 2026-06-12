#include "raylib.h"

int **board;
Vector2 boardSize;

int gameActive;
int currentPlayerIndex;

void SetBoardWidth(int width)
{
    boardSize.x = width;
}
void SetBoardHeight(int height)
{
    boardSize.y = height;
}
Vector2 GetBoardSize()
{
    return boardSize;
}

void GameLogic_Setup()
{
    gameActive = 1;
    currentPlayerIndex = 1;

    int boardSizeX = boardSize.x;
    int boardSizeY = boardSize.y;

    // allocate memory for the board array
    int len = sizeof(int *) * boardSizeY + sizeof(int) * boardSizeX * boardSizeY;
    board = (int **)malloc(len);
    int *bPtr = (int *)(board + boardSizeY);
    for (int row = 0; row < boardSize.y; row++)
    {
        board[row] = (bPtr + boardSizeX * row);
        for (int col = 0; col < boardSizeX; col++)
            board[row][col] = 0;
    }
}

int GetBoardVal(int rowIndex, int columnIndex)
{
    return board[rowIndex][columnIndex];
}
int GetFirstEmptyRowIndex(int columnIndex)
{
    for (int row = boardSize.y - 1; row >= 0; row--)
    {
        if (board[row][columnIndex] == 0)
            return row;
    }
    return -1;
}

int GetCurrentPlayerIndex()
{
    return currentPlayerIndex;
}
void SwitchPlayerTurn()
{
    currentPlayerIndex = currentPlayerIndex == 1 ? 2 : 1;
}

// returns 0 if nothing found, 1 if player 1 won, 2 if player 2 won
int CheckIfFourCellsBelongsToOnePlayer(int y, int x, int direction) // 0 - right, 1 - diagonalDownRight, 2 - down,3 - diagonalDownLeft
{
    switch (direction)
    {
    case 0:

        if (y + 3 >= boardSize.y)
        {
            return 0;
        }
        if (board[y][x] == board[y + 1][x] && board[y][x] == board[y + 2][x] && board[y][x] == board[y + 3][x])
        {
            return board[y][x];
        }
        return 0;
    case 1:
        if (y + 3 >= boardSize.y)
        {
            return 0;
        }
        if (x + 3 >= boardSize.x)
        {
            return 0;
        }
        if (board[y][x] == board[y + 1][x + 1] && board[y][x] == board[y + 2][x + 2] && board[y][x] == board[y + 3][x + 3])
        {
            return board[y][x];
        }
        return 0;
    case 2:
        if (x + 3 >= boardSize.x)
        {
            return 0;
        }
        if (board[y][x] == board[y][x + 1] && board[y][x] == board[y][x + 2] && board[y][x] == board[y][x + 3])
        {
            return board[y][x];
        }
        return 0;
    case 3:
        if (y + 3 >= boardSize.y)
        {
            return 0;
        }
        if (x - 3 < 0)
        {
            return 0;
        }
        if (board[y][x] == board[y + 1][x - 1] && board[y][x] == board[y + 2][x - 2] && board[y][x] == board[y + 3][x - 3])
        {
            return board[y][x];
        }
        return 0;
    }
    return 0;
}
// returns 0 if nothing found, 1 if player 1 won, 2 if player 2 won
int IsGameFinished()
{
    int result = 0;
    for (int row = 0; row < boardSize.y; row++)
    {
        for (int col = 0; col < boardSize.x; col++)
        {
            for (int i = 0; i < 4; i++)
            {
                result = CheckIfFourCellsBelongsToOnePlayer(row, col, i);
                if (result != 0)
                    return result;
            }
        }
    }
    return 0;
}

int IsGameActive()
{
    return gameActive;
}
void GameOver(int winner)
{
    gameActive = false;
}

void PlayerPlaceChip(int rowIndex, int columnIndex)
{
    board[rowIndex][columnIndex] = currentPlayerIndex;

    int gameFinished = IsGameFinished();

    if (gameFinished == 1 || gameFinished == 2)
    { // if one of the players won
        GameOver(gameFinished);
    }
    else
    { // if the game is not finished

        SwitchPlayerTurn();
    }
}
