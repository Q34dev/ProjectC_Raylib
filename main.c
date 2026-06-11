#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

int windowWidth = 800;
int windowHeight = 700;

unsigned int cellCountX = 7;
unsigned int cellCountY = 6;
float cellSize = 60.f;
float cellDist = 10.f;

float cellPosX, cellPosY,startCellPosX;
float cellHalf = 1.f;
int cellTexSize = 128;
float cellTexScale = 1.f;
int colArrowPosY;
Vector2 backRectSize, backRectPos;

Vector2** cellPositions;
float* columnEndPositions;
int** board;

Texture chipRedTex, chipYellowTex;
Texture colArrowTex;

Color player1Color, player2Color;

int currentPlayerIndex = 1;

static void UpdateDrawFrame(void);
void CellGridSetup();
void DrawCell(Vector2 cellPos, int boardVal);
int GetFirstEmptyRowIndex(int columnIndex);
void PlaceChip(int rowIndex, int columnIndex);

int main()
{
    InitWindow(windowWidth, windowHeight, "Connect4");

	chipRedTex = LoadTexture("resources/connect4_chip_red.png");
    chipYellowTex = LoadTexture("resources/connect4_chip_yellow.png");
    colArrowTex = LoadTexture("resources/column_select_arrow.png");

    player1Color = (Color){ 0xFF, 0x00, 0x30, 0xFF };
    player2Color = (Color){ 0xFF, 0x9D, 0x00, 0xFF };

    CellGridSetup();

    // set the size and position of the back rectangle
    backRectSize.x = ((cellSize + cellDist) * cellCountX) + 30.f;
    backRectSize.y = ((cellSize + cellDist) * cellCountY) + 20.f;
	backRectPos.x = (windowWidth * 0.5f) - (backRectSize.x * 0.5f);
    backRectPos.y = (windowHeight * 0.5f) - (backRectSize.y * 0.5f);
    
    #if defined(PLATFORM_WEB)
        emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
    #else
        SetTargetFPS(60);

        while (!WindowShouldClose())
        {
            UpdateDrawFrame();
        }
    #endif

	UnloadTexture(chipRedTex);

    CloseWindow();
    return 0;
}

static void UpdateDrawFrame(void)
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    // draw the player turn text
    char str[128];
    sprintf(str,"Player %d turn",currentPlayerIndex);
    int textWidthHalf = MeasureText(str, 30) * 0.5f;
    DrawText(str, (windowWidth*0.5f)-textWidthHalf, 20, 30, currentPlayerIndex == 1 ? player1Color : player2Color);
    
    // draw the back rectangle
    DrawRectangle(backRectPos.x, backRectPos.y, backRectSize.x, backRectSize.y, BLUE);

    // check mouse position and input
    int mousePosX = GetMouseX();
    if (mousePosX > (startCellPosX-cellHalf-cellDist))
    { // the mouse is over the board
        for (int col = 0; col < cellCountX; col++)
        { // check all columns
            if (mousePosX < columnEndPositions[col])
            { // the mouse is over this column

                // check if there is an empty spot in this column
                int firstEmptyRow = GetFirstEmptyRowIndex(col);
                if (firstEmptyRow < 0) break;

                // draw an arrow above the column
                Vector2 colArrowPos = {cellPositions[0][col].x-cellHalf, colArrowPosY};
                Color arrowColor = currentPlayerIndex == 1 ? player1Color : player2Color;
                DrawTextureEx(colArrowTex, colArrowPos, 0.f, cellTexScale, arrowColor);

                if (IsMouseButtonPressed(0))
                { // if the left mouse button was pressed this frame
                    
                    PlaceChip(firstEmptyRow, col);
                }

                break;
            }
        }
    }

    // draw the cells
    for (int row = 0; row < cellCountY; row++)
    {
        for (int col = 0; col < cellCountX; col++)
        {
            DrawCell(cellPositions[row][col], board[row][col]);
        }
    }

    EndDrawing();
}

void CellGridSetup()
{
    cellTexScale = cellSize / cellTexSize;
	cellHalf = cellSize * 0.5f;

	cellPosX = windowWidth * 0.5f;
    cellPosX -= cellHalf * (cellCountX-1);
    cellPosX -= cellDist * 0.5f * (cellCountX-1);
    startCellPosX = cellPosX;
	
    cellPosY = windowHeight * 0.5f;
    cellPosY -= cellHalf * (cellCountY-1);
    cellPosY -= cellDist * 0.5f * (cellCountY-1);

    // allocate memory for the cellPositions array
    int len = sizeof(Vector2*) * cellCountY + sizeof(Vector2) * cellCountX * cellCountY;
    cellPositions = (Vector2**)malloc(len);
    Vector2* ptr = (Vector2*)(cellPositions + cellCountY);
    for (int row = 0; row < cellCountY; row++)
        cellPositions[row] = (ptr + cellCountX * row);

    // fill out the cellPositions array
	for (int row = 0; row < cellCountY; row++)
	{
		cellPosX = startCellPosX;
		for (int col = 0; col < cellCountX; col++)
		{
			Vector2 cellPos = {cellPosX, cellPosY};
			cellPositions[row][col] = cellPos;

			cellPosX += cellSize + cellDist;
		}
		cellPosY += cellSize + cellDist;
	}

    // allocate memory for the columnEndPositions array
    columnEndPositions = (float*)malloc(sizeof(float) * cellCountX);

    // fill out the columnEndPositions array
	for (int col = 0; col < cellCountX; col++)
	{
		columnEndPositions[col] = cellPositions[0][col].x + cellHalf + cellDist;
	}

    // allocate memory for the board array
    len = sizeof(int*) * cellCountY + sizeof(int) * cellCountX * cellCountY;
    board = (int**)malloc(len);
    int* bPtr = (int*)(board + cellCountY);
    for (int row = 0; row < cellCountY; row++)
    {
        board[row] = (bPtr + cellCountX * row);
        for (int col = 0; col < cellCountX; col++)
            board[row][col] = 0;
    }

    colArrowPosY = cellPositions[0][0].y - cellSize - 50;
}

void DrawCell(Vector2 cellPos, int boardVal)
{
    if (boardVal == 0)
    { // no chip
        DrawCircle(cellPos.x, cellPos.y, cellHalf, DARKBLUE);
    }
    else
    { // red chip (1) or yellow chip (2)
        
        Texture tex = boardVal == 1 ? chipRedTex : chipYellowTex;
        Vector2 texPos = {cellPos.x - cellHalf, cellPos.y - cellHalf};

	    DrawTextureEx(tex, texPos, 0.f, cellTexScale, WHITE);
    }
}

int GetFirstEmptyRowIndex(int columnIndex)
{
    for (int row = cellCountY-1; row >= 0; row--)
    {
        if (board[row][columnIndex] == 0)
            return row;
    }
    return -1;
}

void PlaceChip(int rowIndex, int columnIndex)
{
    board[rowIndex][columnIndex] = currentPlayerIndex;

    // switch the player
    currentPlayerIndex = currentPlayerIndex == 1 ? 2 : 1;
}
