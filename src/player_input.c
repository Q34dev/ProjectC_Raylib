#include "../include/game_logic.h"

void PlaceChip(int rowIndex, int columnIndex)
{
    PlayerPlaceChip(rowIndex, columnIndex);
}

int CheckMouseInput(float minXPos, int cellCountX,  float* columnEndPositions)
{
    // check mouse position and input
    // and return selected column's index

    int selectedColumnIndex = -1;    
    int mousePosX = GetMouseX();
    if (mousePosX >= minXPos)
    { // the mouse is over the board
        for (int col = 0; col < cellCountX; col++)
        { // check all columns
            if (mousePosX < columnEndPositions[col])
            { // the mouse is over this column

                // check if there is an empty spot in this column
                int firstEmptyRow = GetFirstEmptyRowIndex(col);
                if (firstEmptyRow < 0)
                    break;

                selectedColumnIndex = col;

                if (IsMouseButtonPressed(0))
                { // if the left mouse button was pressed this frame

                    PlaceChip(firstEmptyRow, col);
                }

                break;
            }
        }
    }

    return selectedColumnIndex;
}
