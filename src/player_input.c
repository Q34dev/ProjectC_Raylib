#include "../include/game_logic.h"

int mouseOverResetBtn = 0;

void PlaceChip(int rowIndex, int columnIndex)
{
    PlayerPlaceChip(rowIndex, columnIndex);
}

int CheckMouseInput(float minXPos, int cellCountX,  float* columnEndPositions)
{
    // check mouse position and input
    // and return selected column's index

    if (mouseOverResetBtn)
    { // if the mouse cursor is hovering over the reset button instead
        // don't detect the board input
        return -1;
    }

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

void DrawResetButton(int windowHeight)
{
    Vector2 btnSize = { 150.f, 50.f };
    Vector2 btnPos = { 20.f, windowHeight-70.f };

    Rectangle btnRect = { btnPos.x, btnPos.y, btnSize.x, btnSize.y };

    Vector2 mousePos = { 0.f, 0.f };
    mousePos = GetMousePosition();

    if (CheckCollisionPointRec(mousePos, btnRect))
    { // mouse cursor is hovering over the button
        
        DrawRectangle(btnPos.x, btnPos.y, btnSize.x, btnSize.y, LIGHTGRAY);

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        { // pressed the button
            
            ResetGame();
        }

        mouseOverResetBtn = 1;
    }
    else
    { // mouse cursor is not hovering over

        DrawRectangle(btnPos.x, btnPos.y, btnSize.x, btnSize.y, GRAY);

        mouseOverResetBtn = 0;
    }
    
    // draw the button caption
    Vector2 btnTxtPos = btnPos;
    int textWidthHalf = MeasureText("RESET", 20) * 0.5f;
    btnTxtPos.x += (btnSize.x * 0.5f) - textWidthHalf;
    btnTxtPos.y += (btnSize.y * 0.5f) - 10.f;
    DrawText("RESET", btnTxtPos.x, btnTxtPos.y, 20, BLACK);
}
