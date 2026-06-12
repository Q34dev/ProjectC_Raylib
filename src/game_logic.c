#include "raylib.h"

int **board;
Vector2 boardSize;

int currentPlayerIndex;

void GameLogic_Setup(Vector2 cellCount)
{
    currentPlayerIndex = 1;

    boardSize = cellCount;
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
void PlayerPlaceChip(int rowIndex, int columnIndex)
{
    board[rowIndex][columnIndex] = currentPlayerIndex;

    SwitchPlayerTurn();
}

// returns 0 if nothing found, 1 if player 1 won, 2 if player 2 won
int CheckIfFourCellsBelongsToOnePlayer(int y, int x, int direction, int cellCountX, int cellCountY, int **board) // 0 - right, 1 - diagonalDownRight, 2 - down,3 - diagonalDownLeft
{
    switch (direction)
    {
    case 0:

        if (y + 3 >= cellCountY)
        {
            return 0;
        }
        if (board[y][x] == board[y + 1][x] && board[y][x] == board[y + 2][x] && board[y][x] == board[y + 3][x])
        {
            return board[y][x];
        }
        return 0;
    case 1:
        if (y + 3 >= cellCountY)
        {
            return 0;
        }
        if (x + 3 >= cellCountX)
        {
            return 0;
        }
        if (board[y][x] == board[y + 1][x + 1] && board[y][x] == board[y + 2][x + 2] && board[y][x] == board[y + 3][x + 3])
        {
            return board[y][x];
        }
        return 0;
    case 2:
        if (x + 3 >= cellCountX)
        {
            return 0;
        }
        if (board[y][x] == board[y][x + 1] && board[y][x] == board[y][x + 2] && board[y][x] == board[y][x + 3])
        {
            return board[y][x];
        }
        return 0;
    case 3:
        if (y + 3 >= cellCountY)
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
}
// returns 0 if nothing found, 1 if player 1 won, 2 if player 2 won
int IsGameFinished(int cellCountX, int cellCountY, int **board)
{
    int result = 0;
    for (int row = 0; row < cellCountY; row++)
    {
        for (int col = 0; col < cellCountX; col++)
        {
            for (int i = 0; i < 4; i++)
            {
                result = CheckIfFourCellsBelongsToOnePlayer(row, col, i, cellCountX, cellCountY, board);
                if (result != 0)
                    return result;
            }
        }
    }
    return 0;
}
