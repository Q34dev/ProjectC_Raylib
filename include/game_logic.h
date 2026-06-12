#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "../src/game_logic.c"
#include "raylib.h"

void GameLogic_Setup(Vector2 cellCount);

int GetBoardVal(int rowIndex, int columnIndex);
int GetFirstEmptyRowIndex(int columnIndex);

int GetCurrentPlayerIndex();
void SwitchPlayerTurn();
void PlayerPlaceChip(int rowIndex, int columnIndex);

// returns 0 if nothing found, 1 if player 1 won, 2 if player 2 won
int CheckIfFourCellsBelongsToOnePlayer(int y, int x, int direction, int cellCountX, int cellCountY, int **board); // 0 - right, 1 - diagonalDownRight, 2 - down,3 - diagonalDownLeft
// returns 0 if nothing found, 1 if player 1 won, 2 if player 2 won
int IsGameFinished(int cellCountX, int cellCountY, int **board);

#endif
