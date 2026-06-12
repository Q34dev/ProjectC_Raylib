#include "raylib.h"
#include "../include/file_manager.h"

int **board;
Vector2 boardSize = (Vector2){7,6};

int gameActive;
int currentPlayerIndex;
int winnerIndex;
int newGame = 1;

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

// 1 - empty, 0 - not empty
int IsBoardEmpty(int cellCountX, int cellCountY, int **board)
{
    for (int row = 0; row < boardSize.y; row++)
    {
        for (int col = 0; col < boardSize.x; col++)
        {
            if (board[row][col] != 0)
                return 0;
        }
    }
    return 1;
}

void GameLogic_Setup()
{
    gameActive = 1;
    currentPlayerIndex = 1;
    winnerIndex = 0;

    int boardSizeX = boardSize.x;
    int boardSizeY = boardSize.y;

    // allocate memory for the board array
    int len = sizeof(int *) * boardSizeY + sizeof(int) * boardSizeX * boardSizeY;
    board = (int **)malloc(len);
    int *bPtr = (int *)(board + boardSizeY);
    for (int row = 0; row < boardSizeY; row++)
    {
        board[row] = (bPtr + boardSizeX * row);
        for (int col = 0; col < boardSizeX; col++)
            board[row][col] = 0;
    }

    // load the game data from the save file
    LoadGameState(&currentPlayerIndex, boardSizeX, boardSizeY, board);
    newGame = IsBoardEmpty(boardSizeX, boardSizeY, board);
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
    int boardFull = 1;

    for (int row = 0; row < boardSize.y; row++)
    {
        for (int col = 0; col < boardSize.x; col++)
        {
            for (int i = 0; i < 4; i++)
            {
                result = CheckIfFourCellsBelongsToOnePlayer(row, col, i);
                if (result != 0)
                { // if there are 4 chips in a row/column/diagonal
                    // return the index of the owner of those chips
                    return result;
                }
            }

            if (boardFull == 1 && board[row][col] == 0)
            { // if there is at least one empty cell
                boardFull = 0;
            }
        }
    }
    // if neither of the players have won the game yet

    if (boardFull)
        return 3; // draw
    else
        return 0; // game not finished
}
int IsGameNew() { return newGame; }
int IsGameActive()
{
    return gameActive;
}
void GameOver(int winner)
{
    winnerIndex = winner;

    gameActive = 0;
}

int GetWinner()
{ // return 0 if no winner, 1 if player 1 won, 2 if player 2 won & 3 if its a draw
    return winnerIndex;
}

void PlayerPlaceChip(int rowIndex, int columnIndex)
{
    board[rowIndex][columnIndex] = currentPlayerIndex;

    int gameFinished = IsGameFinished();

    if (gameFinished == 1
     || gameFinished == 2
     || gameFinished == 3)
    { // if one of the players won or its a draw

        // save a clear game board to the save file
        ClearGameState(boardSize.x, boardSize.y);

        GameOver(gameFinished);
    }
    else
    { // if the game is not finished

        SwitchPlayerTurn();

        // save the game data to the save file
        SaveGameState(currentPlayerIndex, boardSize.x, boardSize.y, board);
    }
}

void ResetGame()
{
    gameActive = 1;
    currentPlayerIndex = 1;
    winnerIndex = 0;
    newGame = 1;

    // reset the board
    for (int row = 0; row < boardSize.y; row++)
    {
        for (int col = 0; col < boardSize.x; col++)
            board[row][col] = 0;
    }

    // save a clear game board to the save file
    ClearGameState(boardSize.x, boardSize.y);
}
