#ifndef PLAYER_INPUT_H
#define PLAYER_INPUT_H

#include "../src/player_input.c"

void PlaceChip(int rowIndex, int columnIndex);

// returns the selected column's index
int CheckMouseInput(float minXPos, int cellCountX, float* columnEndPositions);

#endif
