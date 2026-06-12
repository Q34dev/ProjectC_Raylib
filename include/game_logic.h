#include "../src/game_logic.c"
int currentPlayerIndex;

int GetCurrentPlayerIndex();

void SwitchPlayer();

// returns 0 if nothing found, 1 if player 1 won, 2 if player 2 won
int IsGameFinished(int cellCountX, int cellCountY, int **board);

// returns 0 if nothing found, 1 if player 1 won, 2 if player 2 won
int CheckIfFourCellsBelongsToOnePlayer(int y, int x, int direction, int cellCountX, int cellCountY, int **board); // 0 - right, 1 - diagonalDownRight, 2 - down,3 - diagonalDownLeft
