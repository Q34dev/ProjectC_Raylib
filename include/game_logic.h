#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "../src/game_logic.c"
#include "raylib.h"

void SetBoardWidth(int width);
void SetBoardHeight(int height);
Vector2 GetBoardSize();

int IsBoardEmpty(int cellCountX, int cellCountY, int **board);

void GameLogic_Setup();

int GetBoardVal(int rowIndex, int columnIndex);
int GetFirstEmptyRowIndex(int columnIndex);

int GetCurrentPlayerIndex();
void SwitchPlayerTurn();

// returns 0 if nothing found, 1 if player 1 won, 2 if player 2 won
int CheckIfFourCellsBelongsToOnePlayer(int y, int x, int direction); // 0 - right, 1 - diagonalDownRight, 2 - down,3 - diagonalDownLeft
// returns 0 if nothing found, 1 if player 1 won, 2 if player 2 won & 3 if its a draw
int IsGameFinished();
int IsGameNew();
int IsGameActive();
void GameOver(int winner);
// returns 0 if no winner, 1 if player 1 won, 2 if player 2 won & 3 if its a draw
int GetWinner();

void PlayerPlaceChip(int rowIndex, int columnIndex);

void ResetGame();

#endif
