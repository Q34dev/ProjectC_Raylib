#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

int windowWidth = 700;
int windowHeight = 600;

unsigned int cellCountX = 4;
unsigned int cellCountY = 3;
float cellSize = 100.f;
float cellDist = 10.f;

float cellPosX, cellPosY,startCellPosX;
float cellHalf = 1.f;
int cellTexSize = 128;
float cellTexScale = 1.f;
Vector2 backRectSize, backRectPos;

Vector2** cellPositions;
float* columnEndPositions;

Texture chipRedTex;

static void UpdateDrawFrame(void);
void CellGridSetup();
void DrawCell(Vector2 cellPos);

int main()
{
    InitWindow(windowWidth, windowHeight, "Connect4");

	chipRedTex = LoadTexture("resources/connect4_chip_red.png");

    CellGridSetup();

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
    
    DrawRectangle(backRectPos.x, backRectPos.y, backRectSize.x, backRectSize.y, BLUE);

    int selectedColIndex = -1;
    Vector2 posOffset = { 0.f, 0.f };
    if (IsMouseButtonDown(0))
    {
        int mousePosX = GetMouseX();
        if (mousePosX > (startCellPosX-(cellSize*0.5f)-cellDist))
        {
            for (int col = 0; col < cellCountX; col++)
            {
                if (mousePosX < columnEndPositions[col])
                {
                    posOffset.y = 10.f;
                    selectedColIndex = col;
                    
                    break;
                }
            }
        }
    }

    for (int row = 0; row < cellCountY; row++)
    {
        for (int col = 0; col < cellCountX; col++)
        {
            Vector2 cellPos = cellPositions[row][col];
            if (selectedColIndex >= 0 && col == selectedColIndex)
            {
                cellPos.x += posOffset.x;
                cellPos.y += posOffset.y;
            }
            DrawCell(cellPos);
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

    int len = sizeof(Vector2*) * cellCountY + sizeof(Vector2) * cellCountX * cellCountY;
    cellPositions = (Vector2**)malloc(len);
    Vector2* ptr = (Vector2*)(cellPositions + cellCountY);
    
    for (int row = 0; row < cellCountY; row++)
    {
        cellPositions[row] = (ptr + cellCountX * row);
    }

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

    columnEndPositions = (float*)malloc(sizeof(float) * cellCountX);
	for (int col = 0; col < cellCountX; col++)
	{
		columnEndPositions[col] = cellPositions[0][col].x + cellHalf + cellDist;
	}
}

void DrawCell(Vector2 cellPos)
{
	Vector2 texPos = {cellPos.x - cellHalf, cellPos.y - cellHalf};
	DrawTextureEx(chipRedTex, texPos, 0.f, cellTexScale, WHITE);
}
