#include "raylib.h"
#include "../include/game_logic.h"
#include "../include/player_input.h"

int windowWidth = 800;
int windowHeight = 700;

int cellCountX;
int cellCountY;
float cellSize = 60.f;
float cellDist = 10.f;

float cellPosX, cellPosY, startCellPosX;
float cellHalf = 1.f;
int cellTexSize = 128;
float cellTexScale = 1.f;
int colArrowPosY;
Vector2 backRectSize, backRectPos;

Vector2 **cellPositions;
float *columnEndPositions;

Texture chipRedTex, chipYellowTex;
Texture colArrowTex;

Color player1Color, player2Color, drawColor;

void CellGridSetup()
{
    cellTexScale = cellSize / cellTexSize;
    cellHalf = cellSize * 0.5f;

    cellPosX = windowWidth * 0.5f;
    cellPosX -= cellHalf * (cellCountX - 1);
    cellPosX -= cellDist * 0.5f * (cellCountX - 1);
    startCellPosX = cellPosX;

    cellPosY = windowHeight * 0.5f;
    cellPosY -= cellHalf * (cellCountY - 1);
    cellPosY -= cellDist * 0.5f * (cellCountY - 1);

    // allocate memory for the cellPositions array
    int len = sizeof(Vector2 *) * cellCountY + sizeof(Vector2) * cellCountX * cellCountY;
    cellPositions = (Vector2 **)malloc(len);
    Vector2 *ptr = (Vector2 *)(cellPositions + cellCountY);
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
    columnEndPositions = (float *)malloc(sizeof(float) * cellCountX);

    // fill out the columnEndPositions array
    for (int col = 0; col < cellCountX; col++)
    {
        columnEndPositions[col] = cellPositions[0][col].x + cellHalf + cellDist;
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

void UpdateDrawFrame()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    // draw the back rectangle
    DrawRectangle(backRectPos.x, backRectPos.y, backRectSize.x, backRectSize.y, BLUE);

    // draw the cells
    for (int row = 0; row < cellCountY; row++)
    {
        for (int col = 0; col < cellCountX; col++)
        {
            DrawCell(cellPositions[row][col], GetBoardVal(row, col));
        }
    }

    int playerIndex = GetCurrentPlayerIndex();

    if (IsGameActive())
    { // if the game is not finished

        // check mouse input
        int selectedColumnIndex = CheckMouseInput(startCellPosX - cellHalf - cellDist, cellCountX, columnEndPositions);

        // draw an arrow above the selected column
        if (selectedColumnIndex >= 0)
        {
            Vector2 colArrowPos = {cellPositions[0][selectedColumnIndex].x - cellHalf, colArrowPosY};
            Color arrowColor = playerIndex == 1 ? player1Color : player2Color;
            DrawTextureEx(colArrowTex, colArrowPos, 0.f, cellTexScale, arrowColor);
        }

        // draw the player turn text
        char str[32];
        sprintf(str, "Player %d turn", playerIndex);
        int textWidthHalf = MeasureText(str, 30) * 0.5f;
        DrawText(str, (windowWidth * 0.5f) - textWidthHalf, 20, 30, playerIndex == 1 ? player1Color : player2Color);
    
        // draw the game state imported info
        if (!IsGameNew())
            DrawText("Game state imported\nfrom the save file", 20, 20, 20, GRAY);
    }
    else
    { // if the game is finished
        
        int winner = GetWinner();
        
        // draw the game over text
        Color textColor = player1Color;
        char str[32];
        if (winner != 3)
        {
            sprintf(str, "Player %d won!", playerIndex);
            textColor =  winner == 1 ? player1Color : player2Color;
        }
        else
        {
            sprintf(str, "A draw!");
            textColor = drawColor;
        }
        int textWidthHalf = MeasureText(str, 30) * 0.5f;
        DrawText(str, (windowWidth * 0.5f) - textWidthHalf, 20, 30, textColor);
    }

    EndDrawing();
}

void GUI_DrawGame()
{
    InitWindow(windowWidth, windowHeight, "Connect4");

    chipRedTex = LoadTexture("resources/connect4_chip_red.png");
    chipYellowTex = LoadTexture("resources/connect4_chip_yellow.png");
    colArrowTex = LoadTexture("resources/column_select_arrow.png");

    player1Color = (Color){0xFF, 0x00, 0x30, 0xFF};
    player2Color = (Color){0xFF, 0x9D, 0x00, 0xFF};
    drawColor = (Color){0xFF, 0x4F, 0x18, 0xFF};

    Vector2 boardSize = GetBoardSize();
    cellCountX = boardSize.x;
    cellCountY = boardSize.y;

    CellGridSetup();

    // set the size and position of the back rectangle
    backRectSize.x = ((cellSize + cellDist) * cellCountX) + 30.f;
    backRectSize.y = ((cellSize + cellDist) * cellCountY) + 20.f;
    backRectPos.x = (windowWidth * 0.5f) - (backRectSize.x * 0.5f);
    backRectPos.y = (windowHeight * 0.5f) - (backRectSize.y * 0.5f);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        UpdateDrawFrame();
    }

    UnloadTexture(chipRedTex);

    CloseWindow();
}

Vector2 GetCellCount()
{
    return (Vector2){ cellCountX, cellCountY };
}

void SetWindowWidth(int width)
{
    windowWidth = width;
}
void SetWindowHeight(int height)
{
    windowHeight = height;
}
